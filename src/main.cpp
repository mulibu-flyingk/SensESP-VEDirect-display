#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"
#include "sensesp/transforms/debounce.h"
#include "sensesp/transforms/lambda_transform.h"
#include "sevedirect/sensors/vedirect.h"
#include <Adafruit_BME280.h>

#include "config.h"
#include "sk_config.h"
#include "utils.h"
#include "render.h"
#include "conversions.h"

using namespace sensesp;

Adafruit_BME280 bme;

unsigned long updateInterval = 10000;
unsigned long pollingInterval = 1000; // in milliseconds
unsigned long timeoutTime = 60000; // 1 minute

#define BATTERY_MONITORING true
#define uS_TO_S_FACTOR 1000000ULL   // Conversion factor from microseconds to seconds
#define TIME_TO_SLEEP  900          // Time for ESP32-E to enter deep sleep

RTC_DATA_ATTR bool lowBat = false;
RTC_DATA_ATTR bool initialBoot = true;  
RTC_DATA_ATTR Measurement currentMeasurement;


class VoltageConsumer : public FloatConsumer {
    public:
    void set(const float& new_value) override {
        currentMeasurement.voltage = new_value;
    }
};

class CurrentConsumer : public FloatConsumer {
    public:
    void set(const float& new_value) override {
        currentMeasurement.current = new_value;
    }
};

class SoCConsumer : public FloatConsumer {
    public:
    void set(const float& new_value) override {
        currentMeasurement.soc = new_value;
    }
};

/**
 * Reads the current temperature from the BME280 sensor and updates the
 * `currentMeasurement` struct with the new value.
 *
 * @return float The updated temperature in Kelvin.
 */
float read_temp_callback() {
  currentMeasurement.temperature = celsius_to_kelvin(bme.readTemperature());
  return currentMeasurement.temperature;
}

/**
 * Reads the current pressure from the BME280 sensor and updates the
 * `currentMeasurement` struct with the new value.
 *
 * @return float The updated pressure in Pascals.
 */
float read_press_callback() {
  currentMeasurement.pressure = bme.readPressure();
  return currentMeasurement.pressure; 
}

/**
 * Reads the current humidity from the BME280 sensor and updates the
 * `currentMeasurement` struct with the new value.
 *
 * @return float The updated humidity as a ratio of 100.0F.
 */
float read_humi_callback() {
  currentMeasurement.humidity = bme.readHumidity() / 100.0F;
  return currentMeasurement.humidity;
}

// Define the function that will be called every time we want
// an updated esp32 state of charge.
float read_esp32_soc_callback() {
  uint32_t batteryMilliVoltage = readBatteryVoltage();
  float batterySoC = calcBatPercent(batteryMilliVoltage, CRIT_LOW_BATTERY_VOLTAGE, MAX_BATTERY_VOLTAGE);
  return batterySoC; 
}

/**
 * Reads the current battery voltage from the esp32 built-in voltage sensor
 * in millivolts and converts it to voltage in volts.
 *
 * @return float The battery voltage in volts.
 */
float read_esp32_voltage_callback() {
  return (float)readBatteryVoltage() / 1000.0F; 
}

// Define the function that will be called every time we want
// an updated e-paper display
bool update_display_callback() {
  debugD("Updating temperature to %f", currentMeasurement.temperature);
  debugD("Updating pressure to %f", currentMeasurement.pressure);
  debugD("Updating humidity to %f", currentMeasurement.humidity);
  debugD("Updating current to %f", currentMeasurement.current);
  debugD("Updating voltage to %f", currentMeasurement.voltage);
  debugD("Updating soc to %f", currentMeasurement.soc);
  return updateOverview(currentMeasurement);
}

// The setup function performs one-time application initialization.
void setup() {
  SetupLogging();

  if (BATTERY_MONITORING) {
    uint32_t batteryVoltage = readBatteryVoltage();
    debugD("Battery voltage: %d mV", int(batteryVoltage));

    // low battery, deep sleep now
    if (batteryVoltage <= LOW_BATTERY_VOLTAGE) {
      if (lowBat == false) { // battery is now low for the first time
        lowBat = true;
        // go to deep sleep and wait for reset
        debugW("Low battery voltage! Going to deep sleep till reset.");
        lowBattery();
        esp_deep_sleep_start();
      }
    } else {
      if (lowBat == true) {
        // battery is no longer low, reset variable in non-volatile storage
        lowBat = false;
      }
    }
  }

  // init display with correct background
  initDisplay(initialBoot);

  bme.begin();

  // finished initial setup
  initialBoot = false;

  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("sensesp-vedirect-display")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    //->set_wifi("My WiFi SSID", "my_wifi_password")
                    //->set_sk_server("192.168.10.3", 80)
                    ->get_app();

  SensESPBaseApp::get_event_loop()->onRepeat(updateInterval, update_display_callback);

  // Create a RepeatSensor with float output that reads the temperature using the function defined above.
  auto* cabin_temp = new RepeatSensor<float>(pollingInterval, read_temp_callback);

  // Send the temperature to the Signal K server as a Float
  cabin_temp->connect_to(new SKOutputFloat(sk_path_cabin_temp, config_path_cabin_temp, metadata_cabin_temp));

  // Create a RepeatSensor with float output that reads the pressure using the function defined above.
  auto* cabin_press = new RepeatSensor<float>(pollingInterval, read_press_callback);

  // Send the pressure to the Signal K server as a Float
  cabin_press->connect_to(new SKOutputFloat(sk_path_cabin_press, config_path_cabin_press, metadata_cabin_press));

  // Create a RepeatSensor with float output that reads the humidity using the function defined above.
  auto* cabin_humi = new RepeatSensor<float>(pollingInterval, read_humi_callback);

  // Send the humidity to the Signal K server as a Float
  cabin_humi->connect_to(new SKOutputFloat(sk_path_cabin_humi, config_path_cabin_humi, metadata_cabin_humi));

  // Create a RepeatSensor with float output that reads the esp32 battery voltage using the function defined above.
  auto* esp32_voltage = new RepeatSensor<float>(pollingInterval, read_esp32_voltage_callback);

  // Send the temperature to the Signal K server as a Float
  esp32_voltage->connect_to(new SKOutputFloat(sk_path_esp32_voltage, config_path_esp32_voltage, metadata_esp32_voltage));

  // Create a RepeatSensor with float output that reads the esp32 battery voltage
  // using the function defined above.
  auto* esp32_soc = new RepeatSensor<float>(pollingInterval, read_esp32_soc_callback);

  // Send the state of charge to the Signal K server as a Float
  esp32_soc->connect_to(new SKOutputFloat(sk_path_esp32_soc, config_path_esp32_soc, metadata_esp32_soc));

  // initialize Serial1 on the opto_in pin
  Serial1.begin(19200, SERIAL_8N1, VEDI_RX, VEDI_TX, false);

  VEDirectInput* vedi = new VEDirectInput(&Serial1);

  vedi->parser.data.channel_1_battery_voltage.connect_to(new VoltageConsumer);
  vedi->parser.data.channel_1_battery_current.connect_to(new CurrentConsumer);
  vedi->parser.data.state_of_charge.connect_to(new SoCConsumer);

  vedi->parser.data.channel_1_battery_voltage.connect_to(new SKOutputFloat("electrical.batteries.house.voltage", 
                        "/Signal K/House Battery Voltage"));

  vedi->parser.data.channel_1_battery_current.connect_to(new SKOutputFloat(
      "electrical.batteries.house.current", "/Signal K/House Battery Current"));

  vedi->parser.data.state_of_charge.connect_to(
      new SKOutputFloat("electrical.batteries.house.capacity.stateOfCharge",
                        "/Signal K/House Battery State Of Charge"));

  vedi->parser.data.instantaneous_power.connect_to(new SKOutputFloat(
      "electrical.batteries.house.power", "/Signal K/House Battery Power"));

  vedi->parser.data.consumed_energy.connect_to(
      new SKOutputFloat("electrical.batteries.house.consumedEnergy",
                        "/Signal K/House Battery Consumed Energy"));

  vedi->parser.data.time_to_go.connect_to(
      new SKOutputFloat("electrical.batteries.house.timeToGo",
                        "/Signal K/House Battery Time To Go"));

  vedi->parser.data.depth_of_deepest_discharge.connect_to(
      new SKOutputFloat("electrical.batteries.house.depthOfDeepestDischarge",
                        "/Signal K/House Battery Depth Of Deepest Discharge"));

  vedi->parser.data.depth_of_last_discharge.connect_to(
      new SKOutputFloat("electrical.batteries.house.depthOfLastDischarge",
                        "/Signal K/House Battery Depth Of Last Discharge"));

  vedi->parser.data.depth_of_average_discharge.connect_to(
      new SKOutputFloat("electrical.batteries.house.depthOfAverageDischarge",
                        "/Signal K/House Battery Depth Of Average Discharge"));

  vedi->parser.data.number_of_charge_cycles.connect_to(
      new SKOutputInt("electrical.batteries.house.numberOfChargeCycles",
                      "/Signal K/House Battery Number Of Charge Cycles"));

  vedi->parser.data.number_of_full_discharges.connect_to(
      new SKOutputInt("electrical.batteries.house.numberOfFullDischarges",
                      "/Signal K/House Battery Number Of Full Discharges"));

  vedi->parser.data.cumulative_energy_drawn.connect_to(
      new SKOutputFloat("electrical.batteries.house.cumulativeEnergyDrawn",
                        "/Signal K/House Battery Cumulative Energy Drawn"));

  vedi->parser.data.minimum_main_voltage.connect_to(
      new SKOutputFloat("electrical.batteries.house.minimumVoltage",
                        "/Signal K/House Battery Minimum Voltage"));

  vedi->parser.data.maximum_main_voltage.connect_to(
      new SKOutputFloat("electrical.batteries.house.maximumVoltage",
                        "/Signal K/House Battery Maximum Voltage"));

  vedi->parser.data.seconds_since_last_full_charge.connect_to(new SKOutputFloat(
      "electrical.batteries.house.secondsSinceLastFullCharge",
      "/Signal K/House Battery Seconds Since Last Full Charge"));

  // Overwrite the default wifi disconnect watchdog
  // send esp32 to deep sleep instead of restarting if no connection can be established
  auto* system_status_controller = sensesp_app->get_system_status_controller();
  system_status_controller
      ->connect_to(new Debounce<SystemStatus>(timeoutTime))
      ->connect_to(new LambdaConsumer<SystemStatus>([](SystemStatus input) {
        debugD("Got system status: %d", (int)input);
        if (input == SystemStatus::kWifiDisconnected ||
            input == SystemStatus::kWifiNoAP) {
          debugW("Unable to connect to wifi for too long; going to deep sleep.");
          esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);   
          debugD("Setup ESP32 to sleep for every %d Seconds", (int)TIME_TO_SLEEP);
          debugD("Going to sleep now");  // We have set the wake up reason. Now we can start go to sleep of the peripherals need to be in deep sleep. If no wake-up source is provided, but deep sleep is initiated, it will sleep forever unless a hardware reset occurs.
          esp_deep_sleep_start();
        }
      }));
}

void loop() { SensESPBaseApp::get_event_loop()->tick(); }
