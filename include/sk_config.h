#ifndef __SK_CONFIG_H__
#define __SK_CONFIG_H__

  #include "sensesp/signalk/signalk_metadata.h"

  using namespace sensesp;

  // Define the SignalK metadata for the cabin temperature sensor value
  const String& units_cabin_temp = "K";
  const String& description_cabin_temp = "Cabin temperature meassured in Kelvin";
  const String& display_name_cabin_temp = "Cabin temperature";
  const String& short_name_cabin_temp = "cabin temp";

  SKMetadata* metadata_cabin_temp = new SKMetadata(units_cabin_temp, description_cabin_temp, display_name_cabin_temp, short_name_cabin_temp);

  // Set the Signal K Path for the output
  const char* sk_path_cabin_temp = "environment.cabin.temperature";
  const String config_path_cabin_temp = "/Signal K/Cabin Temperature";

  // Define the SignalK metadata for the cabin pressure sensor value
  const String& units_cabin_press = "Pa";
  const String& description_cabin_press = "Cabin pressure meassured in pascal";
  const String& display_name_cabin_press = "Cabin pressure";
  const String& short_name_cabin_press = "cabin press";

  SKMetadata* metadata_cabin_press = new SKMetadata(units_cabin_press, description_cabin_press, display_name_cabin_press, short_name_cabin_press);

  // Set the Signal K Path for the output
  const char* sk_path_cabin_press = "environment.cabin.pressure";
  const String config_path_cabin_press = "/Signal K/Cabin Pressure";

  // Define the SignalK metadata for the cabin humidity sensor value
  const String& units_cabin_humi = "ratio";
  const String& description_cabin_humi = "Cabin relative humidity meassured in percent";
  const String& display_name_cabin_humi = "Cabin humidity";
  const String& short_name_cabin_humi = "cabin humi";

  SKMetadata* metadata_cabin_humi = new SKMetadata(units_cabin_humi, description_cabin_humi, display_name_cabin_humi, short_name_cabin_humi);

  // Set the Signal K Path for the output
  const char* sk_path_cabin_humi = "environment.cabin.humidity";
  const String config_path_cabin_humi = "/Signal K/Cabin Humidity";

  // Define the SignalK metadata for the esp32 battery voltage value
  const String& units_esp32_voltage = "V";
  const String& description_esp32_voltage = "ESP32 battery voltage";
  const String& display_name_esp32_voltage = "ESP32 voltage";
  const String& short_name_esp32_voltage = "esp32 V";

  SKMetadata* metadata_esp32_voltage = new SKMetadata(units_esp32_voltage, description_esp32_voltage, display_name_esp32_voltage, short_name_esp32_voltage);

  // Set the Signal K Path for the output
  const char* sk_path_esp32_voltage = "electrical.batteries.esp32.voltage";
  const String config_path_esp32_voltage = "/Signal K/ESP32 Battery Voltage";

  // Define the SignalK metadata for the esp32 battery state of charge value
  const String& units_esp32_soc = "ratio";
  const String& description_esp32_soc = "ESP32 battery state of charge";
  const String& display_name_esp32_soc = "ESP32 SoC";
  const String& short_name_esp32_soc = "esp32 soc";

  SKMetadata* metadata_esp32_soc = new SKMetadata(units_esp32_soc, description_esp32_soc, display_name_esp32_soc, short_name_esp32_soc);

  // Set the Signal K Path for the output
  const char* sk_path_esp32_soc = "electrical.batteries.esp32.soc";
  const String config_path_esp32_soc = "/Signal K/ESP32 Battery State of Charge";

  // Define the SignalK metadata for the house battery voltage value
  const String& units_house_voltage = "V";
  const String& description_house_voltage = "House battery voltage";
  const String& display_name_house_voltage = "House voltage";
  const String& short_name_house_voltage = "house V";

  SKMetadata* metadata_house_voltage = new SKMetadata(units_house_voltage, description_house_voltage, display_name_house_voltage, short_name_house_voltage);

  // Set the Signal K Path for the output
  const char* sk_path_house_voltage = "electrical.batteries.house.voltage";
  const String config_path_house_voltage = "/Signal K/House Battery Voltage";

  // Define the SignalK metadata for the house battery current value
  const String& units_house_current = "A";
  const String& description_house_current = "House battery current";
  const String& display_name_house_current = "House current";
  const String& short_name_house_current = "house A";

  SKMetadata* metadata_house_current = new SKMetadata(units_house_current, description_house_current, display_name_house_current, short_name_house_current);

  // Set the Signal K Path for the output
  const char* sk_path_house_current = "electrical.batteries.house.current";
  const String config_path_house_current = "/Signal K/House Battery Current";

  // Define the SignalK metadata for the house battery state of charge value
  const String& units_house_soc = "ratio";
  const String& description_house_soc = "House battery state of charge";
  const String& display_name_house_soc = "House SoC";
  const String& short_name_house_soc = "house soc";

  SKMetadata* metadata_house_soc = new SKMetadata(units_house_soc, description_house_soc, display_name_house_soc, short_name_house_soc);

  // Set the Signal K Path for the output
  const char* sk_path_house_soc = "electrical.batteries.house.capacity.stateOfCharge";
  const String config_path_house_soc = "/Signal K/House Battery State Of Charge";

  // Define the SignalK metadata for the house battery state of charge value
  const String& units_house_power = "W";
  const String& description_house_power = "House battery power draw";
  const String& display_name_house_power = "House power";
  const String& short_name_house_power = "house W";

  SKMetadata* metadata_house_power = new SKMetadata(units_house_power, description_house_power, display_name_house_power, short_name_house_power);

  // Set the Signal K Path for the output
  const char* sk_path_house_power = "electrical.batteries.house.power";
  const String config_path_house_power = "/Signal K/House Battery Power";

  // Define the SignalK metadata for the house battery time to go
  const String& units_house_ttg = "s";
  const String& description_house_ttg = "House battery time to go";
  const String& display_name_house_ttg = "House time to go";
  const String& short_name_house_ttg = "house ttg";

  SKMetadata* metadata_house_ttg = new SKMetadata(units_house_ttg, description_house_ttg, display_name_house_ttg, short_name_house_ttg);

  // Set the Signal K Path for the output
  const char* sk_path_house_ttg = "electrical.batteries.house.timeToGo";
  const String config_path_house_ttg = "/Signal K/House Battery Time To Go";

  // Define the SignalK metadata for the house battery number of charge cycles
  const String& units_house_charge_cycles = "";
  const String& description_house_charge_cycles = "House battery number of charge cycles";
  const String& display_name_house_charge_cycles = "House charge cycles";
  const String& short_name_house_charge_cycles = "house cycles";

  SKMetadata* metadata_house_charge_cycles = new SKMetadata(units_house_charge_cycles, description_house_charge_cycles, display_name_house_charge_cycles, short_name_house_charge_cycles);

  // Set the Signal K Path for the output
  const char* sk_path_house_charge_cycles = "electrical.batteries.house.numberOfChargeCycles";
  const String config_path_house_charge_cycles = "/Signal K/House Battery Number Of Charge Cycles";

  // Define the SignalK metadata for the house battery number of full discharges
  const String& units_house_full_discharges = "";
  const String& description_house_full_discharges = "House battery number of full discharges";
  const String& display_name_house_full_discharges = "House full discharges";
  const String& short_name_house_full_discharges = "house discharges";

  SKMetadata* metadata_house_full_discharges = new SKMetadata(units_house_full_discharges, description_house_full_discharges, display_name_house_full_discharges, short_name_house_full_discharges);

  // Set the Signal K Path for the output
  const char* sk_path_house_full_discharges = "electrical.batteries.house.numberOfFullDischarges";
  const String config_path_house_full_discharges = "/Signal K/House Battery Number Of Full Discharges";

  // Define the SignalK metadata for the house battery minimum voltage
  const String& units_house_min_voltage = "V";
  const String& description_house_min_voltage = "House battery minimum voltage";
  const String& display_name_house_min_voltage = "House minimum voltage";
  const String& short_name_house_min_voltage = "house minV";

  SKMetadata* metadata_house_min_voltage = new SKMetadata(units_house_min_voltage, description_house_min_voltage, display_name_house_min_voltage, short_name_house_min_voltage);

  // Set the Signal K Path for the output
  const char* sk_path_house_min_voltage = "electrical.batteries.house.minimumVoltage";
  const String config_path_house_min_voltage = "/Signal K/House Battery Minimum Voltage";

  // Define the SignalK metadata for the house battery maximum voltage
  const String& units_house_max_voltage = "V";
  const String& description_house_max_voltage = "House battery maximum voltage";
  const String& display_name_house_max_voltage = "House maximum voltage";
  const String& short_name_house_max_voltage = "house maxV";

  SKMetadata* metadata_house_max_voltage = new SKMetadata(units_house_max_voltage, description_house_max_voltage, display_name_house_max_voltage, short_name_house_max_voltage);

  // Set the Signal K Path for the output
  const char* sk_path_house_max_voltage = "electrical.batteries.house.maximumVoltage";
  const String config_path_house_max_voltage = "/Signal K/House Battery Maximum Voltage";

  // Define the SignalK metadata for the house battery minimum voltage
  const String& units_house_sslfc = "s";
  const String& description_house_sslfc = "House battery seconds since last full charge";
  const String& display_name_house_sslfc = "House sec last full charge";
  const String& short_name_house_sslfc = "house sslfc";

  SKMetadata* metadata_house_sslfc = new SKMetadata(units_house_sslfc, description_house_sslfc, display_name_house_sslfc, short_name_house_sslfc);

  // Set the Signal K Path for the output
  const char* sk_path_house_sslfc = "electrical.batteries.house.secondsSinceLastFullCharge";
  const String config_path_house_sslfc = "/Signal K/House Battery Seconds Since Last Full Charge";

#endif