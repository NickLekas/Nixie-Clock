#ifndef GPS_H
#define GPS_H

#include <Adafruit_GPS.h>

#include "debug.h"
#include "pins.h"

void gpsInit(); //initializes the gps module
void getGPSTime(int &seconds, int &minute, int &hour); //reads the time data from the gps and applies the time zone
void gpsOn(); //turns the gps on
void gpsOff(); //turns the gps off

#endif