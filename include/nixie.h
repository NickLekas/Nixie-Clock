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

void nixieInit(); //initializes the gpio expanders
void dimmingInit(); //initializes the PWM frequency and pin
void dimDown(); //dims the tubes down to ambient light after startup
void dimming(); //dimms the nixie tubes based on ambient light
void cycleDisplay(int &delaySpeed); //cycles the tubes thorugh all numbers
void nixieDisplay(int a, int b, int c, int d, int value); //displays a number on a dube based on binary pins and given number

#endif