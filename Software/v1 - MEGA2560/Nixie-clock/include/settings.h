#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"
#include "pins.h"

void settingsInit();
void getDST(int &DST);
void getTimeMode(bool &twelveHr);
void getTimeZone(int &zone);

#endif

