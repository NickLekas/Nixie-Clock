#ifndef RTC_H
#define RTC_H

#include <SoftwareSerial.h>
#include <RTClib.h>

#include "debug.h"
#include "nixie.h"
#include "gps.h"
#ifdef PCB
  #include "pcbPins.h"
#else
  #include "megaPins.h"
#endif

void getRTCTime(int &minute, int &hour); //reads the time data from the RTC
void setRTCTime(); //sets the RTC time using the GPS
void RTCInit(); //enables the RTC and checks for power loss
void twelveHour(int &hour); //converts the time from 24hr to 12hr
void updateRTC(); //updates the RTC time using the GPS
void readSettings(int &timeZone); //pulls the current dip switch settings for the time zone

#endif