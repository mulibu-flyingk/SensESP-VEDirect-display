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

/**
 * Converts an energy value from WattHours (Wh) to Joules (J).
 * @param watthours The energy in WattHours.
 * @return The equivalent energy in Joules.
 */
float watthours_to_joules(float watthours) {
    return watthours * 3600.0f; // 1 Wh = 3600 J
}

/**
 * Converts an energy value from Joules (J) (Wh) to WattHours.
 * @param joules The energy in Joule.
 * @return The equivalent energy in WattHours.
 */
float joules_to_watthours(float joules) {
    return joules / 3600.0f; // 1 Wh = 3600 J
}

/**
 * Converts a charge value from Coulombs (C) to Ampere-Hours (Ah).
 * @param coulombs The charge in Coulombs.
 * @return The equivalent charge in Ampere-Hours.
 */
float coulombs_to_ampere_hours(float coulombs) {
    return coulombs / 3600.0f;
}

/**
 * Converts a charge value from Ampere-Hours (Ah) to Coulombs (C).
 * @param ampere_hours The charge in Ampere-Hours.
 * @return The equivalent charge in Coulombs.
 */
float ampere_hours_to_coulombs(float ampere_hours) {
    return ampere_hours * 3600.0f;
}