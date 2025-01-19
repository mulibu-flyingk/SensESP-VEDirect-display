#include <Arduino.h>
#include "config.h"
#include <driver/adc.h>
#include <esp_adc_cal.h>

void disableBuiltinLED() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  gpio_hold_en(static_cast<gpio_num_t>(LED_BUILTIN));
  gpio_deep_sleep_hold_en();
  return;
} // end disableBuiltinLED

/* Returns battery voltage in millivolts (mv). */
uint32_t readBatteryVoltage() {
  esp_adc_cal_characteristics_t adc_chars;
  // __attribute__((unused)) disables compiler warnings about this variable
  // being unused (Clang, GCC) which is the case when DEBUG_LEVEL == 0.
  esp_adc_cal_value_t val_type __attribute__((unused));
  adc_power_acquire();
  uint16_t adc_val = analogRead(PIN_BAT_ADC);
  adc_power_release();

  // We will use the eFuse ADC calibration bits, to get accurate voltage
  // readings. The DFRobot FireBeetle Esp32-E V1.0's ADC is 12 bit, and uses
  // 11db attenuation, which gives it a measurable input voltage range of 150mV
  // to 2450mV.
  val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_11db, ADC_WIDTH_BIT_12, 1100, &adc_chars);

  uint32_t batteryVoltage = esp_adc_cal_raw_to_voltage(adc_val, &adc_chars);
  // DFRobot FireBeetle Esp32-E V1.0 voltage divider (1M+1M), so readings are
  // multiplied by 2.
  batteryVoltage *= 2;
  return batteryVoltage;
} // end readBatteryVoltage

/* Returns battery percentage, rounded to the nearest integer.
 * Takes a voltage in millivolts and uses a sigmoidal approximation to find an
 * approximation of the battery life percentage remaining.
 * 
 * This function contains LGPLv3 code from 
 * <https://github.com/rlogiacco/BatterySense>.
 * 
 * Symmetric sigmoidal approximation
 * <https://www.desmos.com/calculator/7m9lu26vpy>
 *
 * c - c / (1 + k*x/v)^3
 */
float calcBatPercent(uint32_t v, uint32_t minv, uint32_t maxv) {
  // slow
  //float p = (110 - (110 / (1 + pow(1.468 * (v - minv)/(maxv - minv), 6))))/100.0F;

  // steep
  //float p = (102 - (102 / (1 + pow(1.621 * (v - minv)/(maxv - minv), 8.1))))/100.0F;

  // normal
  float p = (float)(105 - (105 / (1 + pow(1.724 * (v - minv)/(maxv - minv), 5.5))))/100.0F;
  return p >= 1.0F ? 1.0F : p;
} // end calcBatPercent
