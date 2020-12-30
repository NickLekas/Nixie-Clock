#include "nixie.h"

//Sets the bin to dec pins of the arduino as outputs
void nixieInit() {
    int i;

    //sets all the pins for the nixie drivers as outputs
    for (i = hrTensA; i <= minOnesD; i++) {
        pinMode(i, OUTPUT);
    }

    pinMode(dim, OUTPUT);
    pinMode(light, INPUT);

    return;
}

//sets the PWM frequency of the dimming pin
void dimmingInit() {
    //initializes all timers except timer 0
    InitTimersSafe();

    //Sets the PWM frequency to 350Hz
    SetPinFrequencySafe(dim, 75);

    //sets the starting brightness to max during startup
    pwmWrite(dim, 255);

    return;
}

void dimDown() {
    int lightValue, PWM, i;
    int maxPWM = 245;
    int fade = 10;

    lightValue = analogRead(light); //reads the LDR analog pin
    
    PWM = lightValue / 4; //converts the ADC 12-bit value to 8-bit for PWM

    //keeps the voltage on the tubes from dropping to low to ignite fully/at all
    if(PWM > maxPWM) {
        PWM = maxPWM;
    }

    for(i = 0; i < PWM; i++) {
        pwmWrite(dim, i);
        delay(fade);
    }
}

//photoresistor code
void dimming() {
    int lightValue, PWM;
    int maxPWM = 245;
    
    lightValue = analogRead(light); //reads the current vanalog value of the LDR and stores it in lightValue

    PWM = lightValue / 4; //converts the ADC 12-bit value to 8-bit for PWM

    //pulls the PWM value to max since the voltage divider will never/rarely ever reach max
    if(PWM > maxPWM) {
        PWM = maxPWM;
    }

    pwmWrite(dim, PWM); //writes the PWM value

    return;
}

//Cycles all tubes from 0-9 and 9-0 X times for show and will stop 
void cycleDisplay(int &delaySpeed) {
    int i, cycle = 0, numCycles = 4;

    //cycles though all digites in order X times getting slower on each loop
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
    } while(cycle < numCycles);

    return;
}


void nixieDisplay(int a, int b, int c, int d, int value) {
    digitalWrite(d, (value & 0x08) >> 3);
    digitalWrite(c, (value & 0x04) >> 2);
    digitalWrite(b, (value & 0x02) >> 1);
    digitalWrite(a, value & 0x01);

    return;
}