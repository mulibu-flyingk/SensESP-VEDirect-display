#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "config.h"
#include "utils.h"

void initDisplay(bool initialBoot);
void lowBattery();
bool updateOverview(Measurement measurement);

#endif