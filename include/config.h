#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cstdint>
#include <Arduino.h>

// Set the below constants in "config.cpp"
extern const uint8_t PIN_BAT_ADC;
extern const uint8_t PIN_EPD_BUSY;
extern const uint8_t PIN_EPD_CS;
extern const uint8_t PIN_EPD_RST;
extern const uint8_t PIN_EPD_DC;
extern const uint32_t REFRESH_RATE;
extern const int VEDI_TX;
extern const int VEDI_RX;
extern const int BUTTON_PIN;

// battery voltage levels
extern const uint32_t MAX_BATTERY_VOLTAGE;
extern const uint32_t FULL_BATTERY_VOLTAGE;
extern const uint32_t WARN_BATTERY_VOLTAGE;
extern const uint32_t LOW_BATTERY_VOLTAGE;
extern const uint32_t VERY_LOW_BATTERY_VOLTAGE;
extern const uint32_t CRIT_LOW_BATTERY_VOLTAGE;

// timing settings
extern unsigned long updateInterval;
extern unsigned long pollingInterval;
extern unsigned long timeoutTime;
extern unsigned long long uS_TO_S_FACTOR;
extern const int TIME_TO_SLEEP;

// NON-VOLATILE STORAGE (NVS) NAMESPACE
#define NVS_NAMESPACE "esp32-bwd"

#endif