#include "power.h"

STUSB4500 usbPD;

// Sets the 2 PDO voltages and calculates the currents for a given power limit
// PDO3 has top priority, PDO1 is fixed at 5V
void programPD(int pdoV2, int pdoV3, int pLimit) {
    int pdoI2, pdoI3;

    usbPD.begin();                                          // Initilaizes the STUB4500
    delay(100);                                             // Waits 0.1 seconds for the STUSB to startup

    if(!usbPD.begin()) {                                    // Checks if the STUSB connection was successful
        #ifdef POWER_DEBUG
            Serial.println("Cannot connect to STUSB4500");  // Prints that there was a connection error
        #endif
        while(1);                                           // Loops until the STUSB connetion is established
    }

    #ifdef POWER_DEBUG
        Serial.println("Connected to STUSB4500");           // Prints that the connection was made successfuly
    #endif

    delay(100);                                             // Waits 0.1 seconds for the STUSB to startup

    pdoI2 = pLimit / pdoV2;                                 // Calculates the current limit for PDO2
    pdoI3 = pLimit / pdoV3;                                 // Calculates the cuttent limit for PDO3

    usbPD.setPdoNumber(3);                                  // Sets the STUSB to use 3 

    usbPD.write(DEFAULT);

    //PDO1
    usbPD.setCurrent(1,0.75);                               // Sets the required current for PDO1
    usbPD.setUpperVoltageLimit(1,20);                       // Sets PDO1 voltage upper tolerance to 20%
    usbPD.setLowerVoltageLimit(1,20);                       // Sets PDO1 voltage lower tolerance to 20%

    //PDO2
    usbPD.setVoltage(2,pdoV2);                              // Sets the required voltage for PDO2
    usbPD.setCurrent(2,pdoI2);                              // Sets the required current for PDO2
    usbPD.setLowerVoltageLimit(2,20);                       // Sets PDO2 voltage upper tolerance to 20%
    usbPD.setUpperVoltageLimit(2,20);                       // Sets PDO2 voltage lower tolerance to 20%

    //PDO3
    usbPD.setVoltage(3,pdoV3);                              // Sets the required voltage for PDO3
    usbPD.setCurrent(3,pdoI3);                              // Sets the required current for PDO3
    usbPD.setLowerVoltageLimit(3,20);                       // Sets PDO3 voltage upper tolerance to 20%
    usbPD.setUpperVoltageLimit(3,20);                       // Sets PDO3 voltage lower tolerance to 20%

    #ifdef POWER_DEBUG
        Serial.println("Programmed");                       // Prints that the STUSB was programmed
    #endif

    return;
}