#include "header/gps.h"

//sets up the gps
SoftwareSerial gpsSerial(gpsTX, gpsRX);
Adafruit_GPS gps(&gpsSerial);

//initializes the gps module
void gpsInit() {
    //sets up the gps in RMC mode and 1Hz refresh
    gps.begin(9600);
    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

    return;
}

//pulls 24hr UTC time from the GPS satellites
void getGPSTime(int &seconds, int &minute, int &hour) {
    #ifdef GENERAL_DEBUG
        Serial.println("Waiting for GPS fix");
    #endif

    //checks for new data and loops until a satellite fix is aquired
    do {
        //reads the most recent date from the gps
        gps.read();

        //checks if new data was received
        if (gps.newNMEAreceived()) {
            //parses the new data
            gps.parse(gps.lastNMEA());
        }

    //prints out the satellite fix data
    #ifdef FIX_DEBUG
        Serial.print("Fix: ");
        Serial.print(gps.fix);
        Serial.print("\n");
    #endif

    } while (gps.fix < 1 && !gps.newNMEAreceived());

    #ifdef GENERAL_DEBUG
        Serial.println("GPS fix found");
    #endif

    //gets the time from the new gps data
    minute = gps.minute;
    hour = gps.hour;
    seconds = gps.seconds;

    return;
}