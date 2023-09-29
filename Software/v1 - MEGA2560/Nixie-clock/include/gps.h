#ifndef GPS_H
#define GPS_H

#include <Adafruit_GPS.h>
#include "pins.h"

void gpsInit();                                         // Initializes the gps module
void getGPSTime(int &seconds, int &minute, int &hour);  // Reads the time data from the gps and applies the time zone
void gpsOn();                                           // Turns the gps on
void gpsOff();                                          // Turns the gps off

#endif