#include <Arduino.h>

#include "debug.h"
#include "gps.h"
#include "nixie.h"
#include "pins.h"
#include "nixie.h"
#include "rtc.h"
#include "settings.h"

void startUp(); // Initilizes system
/*
  initilizes rtc
  checks rtc status
    if power loss
      get time from gps
    else
      display current time
*/

void setup() {
  int i;
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");
  #endif
  
  gpsInit();

  settingsInit();

  nixieInit();

  rtcInit();
}

void loop() {
  // put your main code here, to run repeatedly:
}