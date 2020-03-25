#include "nixie.h"

//initializes the gpio expanders
void nixieInit() {
    int i;

    //sets all the pins of the PCF8574 I/O expanders to outputs for cntrolling the nixie drivers
    for (i = hrTensA; i <= minOnesD; i++) {
        pinMode(i, OUTPUT);
    }

    pinMode(dim, OUTPUT);
    pinMode(light, INPUT);

    return;
}

void dimming() {
    int lightValue, PWM;
    
    lightValue = analogRead(light);
    PWM = lightValue / 2;

    analogWrite(dim, PWM);

    return;
}

void cycleDisplay(int &delaySpeed) {
    int i, cycle = 0;

    //cycles though all digites in order four times getting slower on each loop
    do {
        for (i = 0; i < 10; i++) {
            nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, i);
            nixieDisplay(minTensA, minTensB, minTensC, minTensD, i);
            nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, i);
            nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, i);

            delay(delaySpeed);
        }

        delaySpeed *= 1.25;

        cycle++;
    } while(cycle < 4);

    return;
}

void nixieDisplay(int a, int b, int c, int d, int value) {
    digitalWrite(d, (value & 0x08) >> 3);
    digitalWrite(c, (value & 0x04) >> 2);
    digitalWrite(b, (value & 0x02) >> 1);
    digitalWrite(a, value & 0x01);

    return;
}