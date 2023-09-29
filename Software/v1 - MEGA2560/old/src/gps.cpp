#include "gps.h"

Adafruit_GPS gps(&gpsSerial);                               // Creates the GPS object

// Initializes the GPS module
void gpsInit() {
    pinMode(gpsCtrl, OUTPUT);                               // Sets the pin to turn the GPS on and off
    gpsOn();                                                // Turns the GPS on

    gps.begin(9600);                                        // Sets the GPS serial connection to a baudrate of 9600Hz
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);          // Sets the GPS to send minimal data
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);              // Sets the GPS to refresh at a rate of 1Hz

    delay(1000);                                            // Wait 1 second for the GPS to save the settings

    gpsOff();                                               // Turns the GPS off

    return;
}

// Pulls time from the GPS satellites
// Time is in 24Hr UTC format
void getGPSTime(int &seconds, int &minute, int &hour) {
    #ifdef GENERAL_DEBUG
        Serial.println("Waiting for GPS fix");              // Prints the waiting for fix debug message          
    #endif

    do {                                                    // Checks the GPS for new data and loops until a fix is acquired
        delay(1000);
        
        char c = gps.read();                                         // Reads the most recent data from the GPS

        if (gps.newNMEAreceived()) {                        // Checks if new data was received
            gps.parse(gps.lastNMEA());                      // Parses the new data
        }

    #ifdef FIX_DEBUG                                        // Prints out the satellite fix data on one line to the serial monitor
        Serial.print("Fix: ");
        Serial.print(gps.fix);
        Serial.print("\n");
    #endif

    } while(gps.fix < 1 && !gps.newNMEAreceived());         // Breaks the loop once a fix is acquired

    #ifdef GENERAL_DEBUG                                    
        Serial.println("GPS fix found");                    // Indacates when a satellite fix is acquired
    #endif

    minute = gps.minute;                                    // Writes the current minute from the GPS time to the variable 'minute'
    hour = gps.hour;                                        // Writes the current hour from the GPS time to the variable 'hour'
    seconds = gps.seconds;                                  // Writes the current second from the GPS time to the variable 'seconds'

    #ifdef TIME_DEBUG                                       // Prints the the time from the GPS to the serial monitor in the standard hh:mm:ss format
        Serial.print("GPS: ");
        Serial.print(hour);
        Serial.print(":");
        Serial.print(minute);
        Serial.print(":");
        Serial.print(seconds);
        Serial.print("\n");
    #endif

    gpsOff();                                               // Turns off the GPS

    return;
}

// Turns the GPS on
void gpsOn() {
    digitalWrite(gpsCtrl, true);                            // Sets the GPS control pin to high

    return;
}

// Turns the GPS off
void gpsOff() {
    digitalWrite(gpsCtrl, false);                           // Sets the GPS control pin to low

    return;
}