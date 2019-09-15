#ifndef GPS_H
#define GPS_H

#include <Adafruit_GPS.h>

#include "header/pins.h"

void gpsInit(); //initializes the gps module
void getGPSTime(int &seconds, int &minute, int &hour); //reads the time data from the gps and applies the time zone

#endif