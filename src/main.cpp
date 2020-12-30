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

void startUp();                                                     // Initializes the tubes to the current time when first powered

void setup() {
  int i;

  Serial.begin(115200);                                             // Sets Serial0 to 115200 Hz for debug printing

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");                                     // Indicates the the code has started
  #endif

  for(i = dst; i <= one; i++) {                                     // Sets all the pins for the setting switches as inputs with pullups
    pinMode(i, INPUT_PULLUP);                                       
  }

  nixieInit();                                                      // Setup all pins needed to control the tubes

  dimmingInit();                                                    // Sets the PWM frequency and tubes to full brightness

  nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, 0);          // Sets the minute ones tube to display 0
  nixieDisplay(minTensA, minTensB, minTensC, minTensD, 0);          // Sets the minute tens tube to display 0
  nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, 0);              // Sets the hour ones tube to display 0
  nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, 0);              // Sets the hour tens tube to display 0

  gpsInit();                                                        // Initializes the GPS
}

void loop() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;

  startUp();                                                        // Runs the code needed to get everything started

  while(true) {
    dimming();                                                      // Sets the brightness of the nixie tubes based on ambient light

    getRTCTime(minute, hour);                                       // Gets the current time from the RTC

    minOnes = minute % 10;                                          // Uses mod 10 to get the ones digit of the minute
    minTens = (minute - minOnes) / 10;                              // Subtracts the ones digit from the current hour and divides by 10 to get the tens digit of the minute

    hourOnes = hour % 10;                                           // Uses mod 10 to get the ones digit of the hour
    hourTens = (hour - hourOnes) / 10;                              // Subtracts the ones digit from the current hour and divides by 10 to get the tens digit of the hour

    nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, minOnes);  // Writes the current minute ones digit to the minute ones tube
    nixieDisplay(minTensA, minTensB, minTensC, minTensD, minTens);  // Writes the current minute tens digit to the minute tens tube

    //writes the time data out to the hour gpio expander
    nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, hourOnes);     // Writes the current hour ones digit to the hour ones tube
    nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, hourTens);     // Writes the current hour tens digit to the hour tens tube

    #ifdef TIME_DEBUG                                               // Prints the current RTC time to the serial monitor in the standard hh:mm:ss format
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

// Initializes the tubes to the current time when first powered
void startUp() {
  int minute, hour;
  int minOnes, minTens, hourOnes, hourTens;
  int i, delaySpeed = 50;

  RTCInit();                                                        // Sets the RTC time using the GPS or stored time from the battery backup functionality

  dimDown();                                                        // Dims the tubes to the current ambient light

  cycleDisplay(delaySpeed);                                         // Cycles the display for fanfare 
  
  getRTCTime(minute, hour);                                         // Pulls the current time from the RTC

  #ifdef TIME_DEBUG                                                 // Prints the initial time on startup
    Serial.print("Startup: ");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print("\n");
  #endif

    minOnes = minute % 10;                                          // Uses mod 10 to get the ones digit of the minute
    minTens = (minute - minOnes) / 10;                              // Subtracts the ones digit from the current hour and divides by 10 to get the tens digit of the minute

    hourOnes = hour % 10;                                           // Uses mod 10 to get the ones digit of the hour
    hourTens = (hour - hourOnes) / 10;                              // Subtracts the ones digit from the current hour and divides by 10 to get the tens digit of the hour

  
  for(i = 0; i < 10; i++) {                                         // Cycles each tube from 0-9 until the each digit of the current time is on
    if(i <= minOnes) {                                              // Checks if the minute ones tube has reached the current time
      nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, i);
    }
    if(i <= minTens) {                                              // Checks if the minute tens tube has reached the current time
      nixieDisplay(minTensA, minTensB, minTensC, minTensD, i);
    }
    if(i <= hourOnes) {                                             // Checks if the hour ones tube has reached the current time
      nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, i);          
    }
    if(i <= hourTens) {                                             // Checks if the hour tens tube has reached the current time
      nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, i);
    }

    delay(delaySpeed);
  }

  return;
}