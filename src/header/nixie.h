#ifndef NIXIE_H
#define NIXIE_H

#include <PCF8574.h>

#include "header/pins.h"

void nixieInit(); //initializes the gpio expanders
void cycleDisplay(int &delaySpeed); //cycles the tubes thorugh all numbers
void nixieDisplayMinutes(int a, int b, int c, int d, int value); //outputs binary to the minute nixie drivers
void nixieDisplayHours(int a, int b, int c, int d, int value); //outputs binary to the hourr nixie drivers

#endif