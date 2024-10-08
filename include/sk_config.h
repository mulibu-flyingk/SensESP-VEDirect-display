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

#endif