#include <Arduino.h>

#include "config.h"
#include "header/pins.h"
#include "header/gps.h"
#include "header/nixie.h"
#include "header/rtc.h"

void startup(); //cyles the tubes and displays the current time at the end

void setup() {
  int i;

  Serial.begin(115200);

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");
  #endif

  //sets the inputs for the time setting dip switches
  //pinMode(timeMode, INPUT_PULLUP);

  for(i = plusMinus; i <= extra2; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  nixieInit();
  
  //sets the display to 0
  nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, 0);
  nixieDisplay(minTensA, minTensB, minTensC, minTensD, 0);
  nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, 0);
  nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, 0);
  //nixieDisplayMinutes(onesA, onesB, onesC, onesD, 0);
  //nixieDisplayMinutes(tensA, tensB, tensC, tensD, 0);
  //nixieDisplayHours(onesA, onesB, onesC, onesD, 0);
  //nixieDisplayHours(tensA, tensB, tensC, tensD, 0);

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
      nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, minOnes);
      nixieDisplay(minTensA, minTensB, minTensC, minTensD, minTens);
      //nixieDisplayMinutes(onesA, onesB, onesC, onesD, minOnes);
      //nixieDisplayMinutes(tensA, tensB, tensC, tensD, minTens);

      //writes the time data out to the hour gpio expander
      nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, hourOnes);
      nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, hourTens);
      //nixieDisplayHours(onesA, onesB, onesC, onesD, hourOnes);
      //nixieDisplayHours(tensA, tensB, tensC, tensD, hourTens);

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

  //cycles through the digits of the tubes for show
  cycleDisplay(delaySpeed);
  
  //pulls the time from the RTC
  getRTCTime(minute, hour);

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
      nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, i);
      //nixieDisplayMinutes(onesA, onesB, onesC, onesD, i);
    }
    if(i <= minTens) {
      nixieDisplay(minTensA, minTensB, minTensC, minTensD, i);
      //nixieDisplayMinutes(tensA, tensB, tensC, tensD, i);
    }
    if(i <= hourOnes) {
      nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, i);
      //nixieDisplayHours(onesA, onesB, onesC, onesD, i);
    }
    if(i <= hourTens) {
      nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, i);
      //nixieDisplayHours(tensA, tensB, tensC, tensD, i);
    }

    delay(delaySpeed);
  }

  return;
}