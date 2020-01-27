#ifndef NIXIE_H
#define NIXIE_H

#include <PCF8574.h>

#include "header/pins.h"

void nixieInit(); //initializes the gpio expanders
void cycleDisplay(int &delaySpeed); //cycles the tubes thorugh all numbers
void nixieDisplay(int a, int b, int c, int d, int value);

#endif