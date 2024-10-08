#include "conversions.h"

/**
 * Converts a temperature from Kelvin to Celsius.
 * @param kelvin The temperature in Kelvin.
 * @return The equivalent temperature in Celsius.
 */
float kelvin_to_celsius(float kelvin) {
return kelvin - 273.15f;
}

/**
 * Converts a temperature from Celsius to Kelvin.
 * @param celsius The temperature in Celsius.
 * @return The equivalent temperature in Kelvin.
 */
float celsius_to_kelvin(float celsius) {
return celsius + 273.15f;
}

/**
 * Converts a pressure from Hectopascals (hPa) to Pascals (Pa).
 * @param hectopascals The pressure in Hectopascals.
 * @return The equivalent pressure in Pascals.
 */
float hectopascals_to_pascals(float hectopascals) {
return hectopascals * 100.f;
}

/**
 * Converts a pressure from Pascals (Pa) to Hectopascals (hPa).
 * @param pascals The pressure in Pascals.
 * @return The equivalent pressure in Hectopascals.
 */
float pascals_to_hectopascals(float pascals) {
return pascals / 100.f;
}
