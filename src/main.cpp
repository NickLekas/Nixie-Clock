#include <Arduino.h>

#include "debug.h"
#include "gps.h"
#include "nixie.h"
#include "rtc.h"
#ifdef PCB
  #include "pcbPins.h"
#else
  #include "megaPins.h"
#endif


void startUp(); //cyles the tubes and displays the current time at the end

void setup() {
  int i;

  Serial.begin(115200);

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");
  #endif

  for(i = plusMinus; i <= extra2; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  nixieInit();

  dimmingInit();

  dimming();
  
  //sets the display to 0
  nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, 0);
  nixieDisplay(minTensA, minTensB, minTensC, minTensD, 0);
  nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, 0);
  nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, 0);

  gpsInit();

  //gives the gps 1 second to start up
  delay(1000);
}

void loop() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;

  startUp();

  while(true) {
    //sets the brightness of the nixie tubes based on ambient light
    dimming();

    //pulls time from the RTC
    getRTCTime(minute, hour);

    //parses the minute data for the tens and ones digits
    minOnes = minute % 10;
    minTens = (minute - minOnes) / 10;

    //parses the hour data for the tens and ones digits
    hourOnes = hour % 10;
    hourTens = (hour - hourOnes) / 10;

    //writes the time data out to the minute gpio expander
    nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, minOnes);
    nixieDisplay(minTensA, minTensB, minTensC, minTensD, minTens);

    //writes the time data out to the hour gpio expander
    nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, hourOnes);
    nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, hourTens);

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
    }
  }

void startUp() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;
  int i, delaySpeed = 50;

  //sets the brightness of the nixie tubes based on ambient light
  dimming();

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
    }
    if(i <= minTens) {
      nixieDisplay(minTensA, minTensB, minTensC, minTensD, i);
    }
    if(i <= hourOnes) {
      nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, i);
    }
    if(i <= hourTens) {
      nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, i);
    }

    delay(delaySpeed);
  }

  return;
}