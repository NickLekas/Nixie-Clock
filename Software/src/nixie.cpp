#include "nixie.h"

// Setup all pins needed to control the tubes
void nixieInit() {
    int i;

    for (i = hrTensA; i <= minOnesD; i++) {                             // Sets all the pins for the nixie drivers as outputs
        pinMode(i, OUTPUT);
    }

    pinMode(dim, OUTPUT);                                               // Sets the dimming pin as an output
    pinMode(light, INPUT);                                              // Sets the analog pin for the LDR as an input

    return;
}

// Sets the PWM frequency of the dimming pin
void dimmingInit() {
    InitTimersSafe();                                                   // Initializes all timers except for 0

    SetPinFrequencySafe(dim, 75);                                       // Sets the dimming PWM frequncy to 75 Hz so there is no audible coil whine

    pwmWrite(dim, 0);                                                   // Sets the intial brightness to max surring startup so it's always visable durring startup

    return;
}

void dimDown() {
    int lightValue, PWM, i;
    int maxPWM = 250;
    int fade = 10;

    lightValue = analogRead(light);                                     // Reads the current analog value of the LDR and stores it in lightValue 0 = bright, 1024 = dark

    PWM = lightValue / 4;                                               // Converts the ADC 12-bit light value to 8-bit for PWM

    if(PWM > maxPWM) {                                                  // Checks if PWM value is too high to fully ignite the tubes
        PWM = maxPWM;                                                   // Sets the the PWM value to a lower predetermined value
    }

    for(i = 0; i < PWM; i++) {                                          // Dims the tubes to the current light value
        pwmWrite(dim, i);                                               // Writes the current value of 'i' to the PWM pin
        delay(fade);                                                    // Waits X time to control the speed of the dimmnig
    }
}

// Reads the current value from the photoresistor and modifies the current PWM output
void dimming() {
    int lightValue, PWM;
    int maxPWM = 250;
    
    lightValue = analogRead(light);                                     // Reads the current analog value of the LDR and stores it in lightValue 0 = bright, 1024 = dark

    PWM = lightValue / 4;                                               // Converts the ADC 12-bit light value to 8-bit for PWM

    if(PWM > maxPWM) {                                                  // Checks if PWM value is too high to fully ignite the tubes
        PWM = maxPWM;                                                   // Sets the the PWM value to a lower predetermined value
    }

    pwmWrite(dim, PWM);                                                 // Sets the PWM output to the new value

    return;
}

// Cycles all tubes from 0-9 X times for show and will stop 
void cycleDisplay(int &delaySpeed) {
    int i;
    int cycle = 0;
    int numCycles = 4;

    do {                                                                // Cycles through 0-9 X times getting slower on each loop
        for (i = 0; i < 10; i++) {
            nixieDisplay(minOnesA, minOnesB, minOnesC, minOnesD, i);    // Sets the minute ones tube to the current 'i' value
            nixieDisplay(minTensA, minTensB, minTensC, minTensD, i);    // Sets the minute tens tube to the current 'i' value
            nixieDisplay(hrOnesA, hrOnesB, hrOnesC, hrOnesD, i);        // Sets the hour ones tube to the current 'i' value
            nixieDisplay(hrTensA, hrTensB, hrTensC, hrTensD, i);        // Sets the hour tens tube to the current 'i' value

            delay(delaySpeed);                                          // Waits X time to control the speed of the cycle
        }

        delaySpeed *= 1.25;                                             // Increases the loop speed after each 0-9 cycle

        cycle++;
    } while(cycle < numCycles);

    return;
}

// Converts a decimal number to a 4-bit binary number for controlling the nixie drivers
void nixieDisplay(int a, int b, int c, int d, int value) {
    digitalWrite(d, (value & 0x08) >> 3);                               // Gets bit 3 of the decimal input, shifts it to bit 0, and stores it to the variable 'd'
    digitalWrite(c, (value & 0x04) >> 2);                               // Gets bit 2 of the decimal input, shifts it to bit 0, and stores it to the variable 'c'
    digitalWrite(b, (value & 0x02) >> 1);                               // Gets bit 1 of the decimal input, shifts it to bit 0, and stores it to the variable 'b'
    digitalWrite(a, value & 0x01);                                      // Gets bit 0 of the decimal input, and stores it to the variable 'a'                

    return;
}