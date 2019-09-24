#include <Arduino.h>

#include "header/pins.h"
#include "header/config.h"
#include "header/gps.h"
#include "header/nixie.h"
#include "header/rtc.h"

void startup(); //cyles the tubes and displays the current time at the end

void setup() {
  Serial.begin(115200);

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");
  #endif

  nixieInit();
  
  //sets the display to 0
  nixieDisplayMinutes(onesA, onesB, onesC, onesD, 0);
  nixieDisplayMinutes(tensA, tensB, tensC, tensD, 0);
  nixieDisplayHours(onesA, onesB, onesC, onesD, 0);
  nixieDisplayHours(tensA, tensB, tensC, tensD, 0);

  gpsInit();

  //gives the gps 1 second to start up
  delay(1000);
}

void loop() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;
  int last = -1, loop = 0;

  startup();

  while(true) {
    //pulls time from the RTC
    getRTCTime(minute, hour);

    //checks if the time has changed from the last time get
    if(last != minute) {
      //parses the minute data for the tens and ones digits
      minOnes = minute % 10;
      minTens = (minute - minOnes) / 10;

      //parses the hour data for the tens and ones digits
      hourOnes = hour % 10;
      hourTens = (hour - hourOnes) / 10;

      //writes the time data out to the minute gpio expander
      nixieDisplayMinutes(onesA, onesB, onesC, onesD, minOnes);
      nixieDisplayMinutes(tensA, tensB, tensC, tensD, minTens);

      //writes the time data out to the hour gpio expander
      nixieDisplayHours(onesA, onesB, onesC, onesD, hourOnes);
      nixieDisplayHours(tensA, tensB, tensC, tensD, hourTens);

      //prints the time to the serial monitor
      #ifdef TIME_DEBUG
        Serial.print("RTC Time: ");
        Serial.print(hourTens);
        Serial.print(hourOnes);
        Serial.print(":");
        Serial.print(minTens);
        Serial.print(minOnes);
        Serial.print("\n");
      #endif

      //keeps track of the previous minute to compare with the next gps read cycle
      last = minute;

      //syncs the time updates to be every 60 seconds on the first loop and then sleeps the arduino ~60 seconds
      if(loop < 1) {
        loop++;
      }
      else {
        delay(58500);
      }
    }
  }
}

void startup() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;
  int i, delaySpeed = 50;

  //sets the RTC time using the GPS
  setRTCTime();
  //pulls the time from the RTC
  getRTCTime(minute, hour);

  //cycles through the digits of the tubes for show
  cycleDisplay(delaySpeed);

  //prints the time data
  #ifdef TIME_DEBUG
    Serial.print("Startup: ");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print("\n");
  #endif

  //parses the minute data for the tens and ones digits
  minOnes = minute % 10;
  minTens = (minute - minOnes) / 10;

  //parses the hour data for the tens and ones digits
  hourOnes = hour % 10;
  hourTens = (hour - hourOnes) / 10;

  //cycles trough all the digits until the the correct number is found
  for(i = 0; i < 10; i++) {
    if(i <= minOnes) {
      nixieDisplayMinutes(onesA, onesB, onesC, onesD, i);
    }
    if(i <= minTens) {
      nixieDisplayMinutes(tensA, tensB, tensC, tensD, i);
    }
    if(i <= hourOnes) {
      nixieDisplayHours(onesA, onesB, onesC, onesD, i);
    }
    if(i <= hourTens) {
      nixieDisplayHours(tensA, tensB, tensC, tensD, i);
    }

    delay(delaySpeed);
  }

  return;
}