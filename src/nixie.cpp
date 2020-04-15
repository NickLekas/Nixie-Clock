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

//sets the PWM frequency of the dimming pin
void dimmingInit() {
    InitTimersSafe();
    //(16MHz / 1024) / 256 = 61.03515625
    SetPinFrequencySafe(dim, 61.03515625);

    //sets the starting brightness to max during startup
    pwmWrite(dim, 255);

    return;
}

void dimDown() {
    int lightValue, PWM, invert, i;
    int minValue = 5;
    int fade = 10;

    lightValue = analogRead(light); //reads the LDR analog pin
    
    invert = 1024 - lightValue; //subtracts the analog value from the max possible value to invert it

    PWM = invert / 4; //converts the ADC 12-bit value to 8-bit for PWM

    //keeps the voltage on the tubes from dropping to low to ignite fully/at all
    if(PWM < minValue) {
        PWM = minValue;
    }

    for(i = 255; i > PWM; i--) {
        pwmWrite(dim, i);
        delay(fade);
    }
}

//photoresistor code
void dimming() {
    int lightValue, PWM, invert;
    int minValue = 5;
    int maxValue = 210;
    
    lightValue = analogRead(light); //reads the LDR analog pin
    
    invert = 1024 - lightValue; //subtracts the analog value from the max possible value to invert it

    PWM = invert / 4; //converts the ADC 12-bit value to 8-bit for PWM

    //keeps the voltage on the tubes from dropping to low to ignite fully/at all
    if(PWM < minValue) {
        PWM = minValue;
    }

    //pulls the PWM value to max since the voltage divider will never/rarely ever reach max
    if(PWM > maxValue) {
        PWM = 255;
    }

    //Serial.println(PWM);

    pwmWrite(dim, PWM); //writes the PWM value

    return;
}


/*
//pot testing code
void dimming() {
    int lightValue, PWM;

    lightValue = analogRead(light);

    PWM = lightValue / 4;

    Serial.println(PWM);

    pwmWrite(dim, PWM);

    return;
}
*/

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