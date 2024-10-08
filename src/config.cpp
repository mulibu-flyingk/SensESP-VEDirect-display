#include <Arduino.h>
#include "config.h"

// PINS
// The configuration below is intended for use with the project's official 
// wiring diagrams using the FireBeetle 2 ESP32-E microcontroller board.
//
// Note: LED_BUILTIN pin will be disabled to reduce power draw.  Refer to your
//       board's pinout to ensure you avoid using a pin with this shared 
//       functionality.
//
// ADC pin used to measure battery voltage
const uint8_t PIN_BAT_ADC  = 34; // 36 for micro-usb firebeetle
// Pins for E-Paper Driver Board
const uint8_t PIN_EPD_BUSY = 17;
const uint8_t PIN_EPD_RST  = 16;
const uint8_t PIN_EPD_DC   = 4;
const uint8_t PIN_EPD_CS   = 12;

//Pins for the Victron Energy Direct connection
const int VEDI_TX = 25;
const int VEDI_RX = 26;

// Define the GPIO pin where the button is connected
const int BUTTON_PIN = 14;

// define refresh rate
const uint32_t REFRESH_RATE = 15000;
// esp32 battery voltage levels
const uint32_t MAX_BATTERY_VOLTAGE      = 4200; // (millivolts)
const uint32_t WARN_BATTERY_VOLTAGE     = 3400; // (millivolts)
const uint32_t LOW_BATTERY_VOLTAGE      = 3200; // (millivolts)
const uint32_t VERY_LOW_BATTERY_VOLTAGE = 3100; // (millivolts)
const uint32_t CRIT_LOW_BATTERY_VOLTAGE = 3000; // (millivolts)