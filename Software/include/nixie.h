#ifndef NIXIE_H
#define NIXIE_H

#include <Arduino.h>
#include <PWM.h>

#include "debug.h"
#ifdef PCB
  #include "pcbPins.h"
#else
  #include "megaPins.h"
#endif

void nixieInit();                                           // Initializes the gpio expanders
void dimmingInit();                                         // Initializes the PWM frequency and pin
void dimDown();                                             // Dims the tubes down to ambient light after startup
void dimming();                                             // Dims the nixie tubes based on ambient light
void cycleDisplay(int &delaySpeed);                         // Cycles the tubes thorugh all numbers
void nixieDisplay(int a, int b, int c, int d, int value);   // Displays a number on a tube based on binary pins and given number

#endif