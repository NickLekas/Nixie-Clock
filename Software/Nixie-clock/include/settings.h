#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"
#include "pins.h"

void settingsInit();


#endif

void settingsInit() {
    int i;

    for(i = extra1; i <= dst; i++) {
        pinMode(i, INPUT_PULLUP);
    }
}