#include "header/nixie.h"

//sets up the PCF8574 GPIO extenders
PCF8574 minute(0x20);
PCF8574 hour(0x21);

//initializes the gpio expanders
void nixieInit() {
    int i;

    //sets all the pins of the PCF8574 I/O expanders to outputs for cntrolling the nixie drivers
    for (i = 0; i < 8; i++) {
        minute.pinMode(i, OUTPUT);
        hour.pinMode(i, OUTPUT);
    }
    minute.begin();
    hour.begin();

    return;
}

void cycleDisplay(int &delaySpeed) {
    int i, cycle = 0;

    //cycles though all digites in order four times getting slower on each loop
    do {
        for (i = 0; i < 10; i++) {
            nixieDisplayMinutes(onesA, onesB, onesC, onesD, i);
            nixieDisplayMinutes(tensA, tensB, tensC, tensD, i);
            nixieDisplayHours(onesA, onesB, onesC, onesD, i);
            nixieDisplayHours(tensA, tensB, tensC, tensD, i);

            delay(delaySpeed);
        }

        delaySpeed *= 1.25;

        cycle++;
    } while (cycle < 4);

    return;
}

//writes the given value to the minute gpio expander
void nixieDisplayMinutes(int a, int b, int c, int d, int value) {
    minute.digitalWrite(d, (value & 0x08) >> 3);
    minute.digitalWrite(c, (value & 0x04) >> 2);
    minute.digitalWrite(b, (value & 0x02) >> 1);
    minute.digitalWrite(a, value & 0x01);

    return;
}

//writes the given value to the hour gpio expandr
void nixieDisplayHours(int a, int b, int c, int d, int value) {
    hour.digitalWrite(d, (value & 0x08) >> 3);
    hour.digitalWrite(c, (value & 0x04) >> 2);
    hour.digitalWrite(b, (value & 0x02) >> 1);
    hour.digitalWrite(a, value & 0x01);

    return;
}