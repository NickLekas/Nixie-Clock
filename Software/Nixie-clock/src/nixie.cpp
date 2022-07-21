#include "nixie.h"

void nixieInit() {
    int i;

    for (i = minOnesA; i <= minTensC; i++) {
        pinMode(i, OUTPUT);
    }

    for (i = hrOnesA; i <= hrTensC; i++) {
        pinMode(i, OUTPUT);
    }

    pinMode(dim, OUTPUT);
    pinMode(light, OUTPUT);

    return;
}

void dimming() {
    int lightValue, PWM;
    int maxPWM = 250;
    int minPWM = 2;
    
    lightValue = analogRead(light);                                     // Reads the current analog value of the LDR and stores it in lightValue 0 = bright, 1024 = dark

    PWM = lightValue / 4;                                               // Converts the ADC 12-bit light value to 8-bit for PWM

    if(PWM > maxPWM) {                                                  // Checks if PWM value is too high to fully ignite the tubes
        PWM = maxPWM;                                                   // Sets the the PWM value to a lower predetermined value
    }

    if(PWM < minPWM) {
        PWM = minPWM;
    }

    analogWrite(dim, PWM);                                              // Sets the PWM output to the new value

    return;
}


void nixieDisplay(int a, int b, int c, int d, int value) {
    digitalWrite(d, (value & 0x08) >> 3);                               // Gets bit 3 of the decimal input, shifts it to bit 0, and stores it to the variable 'd'
    digitalWrite(c, (value & 0x04) >> 2);                               // Gets bit 2 of the decimal input, shifts it to bit 0, and stores it to the variable 'c'
    digitalWrite(b, (value & 0x02) >> 1);                               // Gets bit 1 of the decimal input, shifts it to bit 0, and stores it to the variable 'b'
    digitalWrite(a, value & 0x01);                                      // Gets bit 0 of the decimal input, and stores it to the variable 'a'                

    return;
}