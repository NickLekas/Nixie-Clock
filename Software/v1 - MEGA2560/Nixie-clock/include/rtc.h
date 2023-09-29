#ifndef RTC_H
#define RTC_H

#include <SoftwareSerial.h>
#include <RTClib.h>

#include "debug.h"
#include "nixie.h"
#include "gps.h"
#include "pins.h"

void getRTCTime(int &minute, int &hour);  // Reads the time data from the RTC
void setRTCTime();                        // Sets the RTC time using the GPS
void rtcInit();                           // Enables the RTC and checks for power loss
void twelveHour(int &hour);               // Converts the time from 24hr to 12hr
void updateRTC();                         // Updates the RTC time using the GPS
void readSettings(int &timeZone);         // Pulls the current dip switch settings for the time zone

#endif