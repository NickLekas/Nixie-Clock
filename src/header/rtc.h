#ifndef RTC_H
#define RTC_H

#include <SoftwareSerial.h>
#include <RTClib.h>

#include "config.h"
#include "header/pins.h"
#include "header/nixie.h"
#include "header/gps.h"

void getRTCTime(int &minute, int &hour); //reads the time data from the RTC
void setRTCTime(); //sets the RTC time using the GPS
void twelveHour(int &hour); //converts the time from 24hr to 12hr
void updateRTC();

#endif