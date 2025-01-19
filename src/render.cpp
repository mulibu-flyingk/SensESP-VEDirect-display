#include <algorithm>
#include <initializer_list>

// libraries for ePaper
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include "config.h"
#include "utils.h"

// background image header files
#include "backgrounds/weather.h"
#include "backgrounds/low_esp32_battery.h"

#include "conversions.h"

// ePaper Waveshare 2.9" black&white init and pin out
// GDEM029T94 128x296, SSD1680, Waveshare 2.9" V2 variant
GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> display(GxEPD2_290_T94_V2(PIN_EPD_CS, PIN_EPD_DC, PIN_EPD_RST, PIN_EPD_BUSY));

// right side of the weather value textboxes
uint16_t x = 83;
// right side of the battery value textboxes
uint16_t x1 = 240;

/* Initialize e-paper display */
void initDisplay(bool initialBoot) {
  display.init(0, initialBoot);

  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(3);
  display.setFont(&FreeMonoBold12pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do {
    display.drawXBitmap(0, 0, weather, 296, 128, GxEPD_BLACK);
  }
  while (display.nextPage());
}


/* update e-paper with low battery warning */
void lowBattery() {
  display.init(0, true);

  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(3);
  display.setFont(&FreeMonoBold12pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do {
    display.drawXBitmap(0, 0, low_esp32_battery, 296, 128, GxEPD_BLACK);  
  }
  while (display.nextPage());
}

bool updateOverview(Measurement measurement) {
  // int16_t tbx, tby; uint16_t tbw, tbh;
  // display.getTextBounds(tempString, x, y, &tbx, &tby, &tbw, &tbh);
  uint16_t y = 0;
  uint16_t x1 = 40;
  uint16_t x2 = 190;
  uint16_t w1 = 60;
  uint16_t w2 = 80;
  uint16_t h = display.height();
  uint16_t first_line = 28;
  uint16_t second_line = 70;
  uint16_t third_line = 110;

  char tempString[32];
  snprintf(tempString, sizeof(tempString), "%.0f", kelvin_to_celsius(measurement.temperature));

  char presString[32];
  snprintf(presString, sizeof(presString), "%.0f", pascals_to_hectopascals(measurement.pressure));

  char humString[32];
  snprintf(humString, sizeof(humString), "%.0f", measurement.humidity * 100.0F);

  char currentString[32];
  snprintf(currentString, sizeof(currentString), "%.2f", measurement.current);

  char voltageString[32];
  snprintf(voltageString, sizeof(voltageString), "%.2f", measurement.voltage);

  char socString[32];
  snprintf(socString, sizeof(socString), "%.0f", measurement.soc * 100.0F);

  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawXBitmap(0, 0, weather, 296, 128, GxEPD_BLACK);
    display.setCursor(x1, first_line);
    display.print(tempString);
    display.setCursor(x1, second_line);
    display.print(presString);
    display.setCursor(x1, third_line);
    display.print(humString);
    display.setCursor(x2, first_line);
    display.print(currentString);
    display.setCursor(x2, second_line);
    display.print(voltageString);
    display.setCursor(x2, third_line);
    display.print(socString);
  }
  while (display.nextPage());

  display.hibernate();

  return true;
}