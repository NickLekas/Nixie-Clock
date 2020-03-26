#ifndef NIXIE_H
#define NIXIE_H

#include <Arduino.h>
#include "debug.h"
#ifdef PCB
  #include "pcbPins.h"
#else
  #include "megaPins.h"
#endif

void nixieInit(); //initializes the gpio expanders
void dimming();
void cycleDisplay(int &delaySpeed); //cycles the tubes thorugh all numbers
void nixieDisplay(int a, int b, int c, int d, int value);

#endif