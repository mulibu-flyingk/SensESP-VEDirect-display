#ifndef __DISPLAY_UTILS_H__
#define __DISPLAY_UTILS_H__

typedef struct strRec {
	float	temperature;
	float pressure;
  float humidity;
  float current;
  float voltage;
  float soc;
} Measurement;

uint32_t readBatteryVoltage();
float calcBatPercent(uint32_t v, uint32_t minv, uint32_t maxv);

#endif