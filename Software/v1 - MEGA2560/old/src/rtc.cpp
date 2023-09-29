#include "rtc.h"

RTC_DS3231 rtc;                                                 // Initializes the RTC object

// Enables the RTC and checks for power loss
// If there was a power loss, sets time using the GPS
// If no power loss, useses last know time and will be updated at 3am local time
void RTCInit() {
    rtc.begin();                                                // Initializes the RTC

    if(rtc.lostPower()) {                                       // Checks if the RTC lost power
        #ifdef TIME_DEBUG                                       // Prints that power was lost to the serial monitor
            Serial.println("power loss");
        #endif

        #ifdef SET_RTC
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        #else
            setRTCTime();                                       // Sets the RTC time using the GPS
        #endif
    }

    return;
}

// RTC time is stored as 24hr UTC time
void setRTCTime() {
    int seconds, minute, hour;

    gpsOn();                                                    // Turns on the GPS

    getGPSTime(seconds, minute, hour);                          // Gets the current time from the GPS

    rtc.adjust(DateTime(1970, 1, 1, hour, minute, seconds));    // Stores the GPS time in the RTC, sets the date to the start of UNIX time since the data isn't needed

    return;
}

// Gets the time from the RTC and converts it to the the users time zone and to 12 Hr formtat if selected
void getRTCTime(int &minute, int &hour) {
    int timeZone;

    DateTime now = rtc.now();                                   // Gets the current time from the RTC

    minute = now.minute();                                      // Gets the current minute from the fetched RTC data
    hour = now.hour();                                          // Gets the current hour from the fetched RTC data

    readSettings(timeZone);                                     // Reads the switch settings for the set time zone

    hour += timeZone;                                           // Applies the time zone value to the hour
    
    if(hour < 0) {                                              // Checks if the adjusted time is less than 24
        hour += 24;                                             // If the adjusted time is less than 0, add 24                
    }
    else if(hour > 23) {                                        // Checks if the adjusted time is greater than 24
        hour -= 24;                                             // If the adjusted time is greater than 24, subtract 24
    }

    if(digitalRead(timeMode) == LOW) {                          // Checks if the 12 hour switch is toggled
        twelveHour(hour);                                       // Converts the time to 12 Hr format
    }

    return;
}

// Updates the RTC time using the GPS and maintains the tubes
// This will occur every day at 3am local time when the user is likely asleep
void updateRTC() {
    int cycleSpeed = 50;

    cycleDisplay(cycleSpeed);                                   // Cycles the display so all digets get used once each day to extend their life

    setRTCTime();                                               // Updates the RTC using the GPS

    return;
}

//converts 24hr time to 12hr time
void twelveHour(int &hour) {
    if(hour == 0) {                                             // Checks if the hour is 0
        hour = 12;                                              // Sets the hour to 12 if it's 0
    }
    else if(hour > 12) {                                        // Checks if the hour is greater than 12
        hour -= 12;                                             // Subtracts 12 from the hour if it's greater than 12
    }

    return;
}

// Reads settings switches 3-7 as 5-bit signed binary to set the time zone
// Reads each bit and sums the decimal values to set the time zone
void readSettings(int &timeZone) {

    if(digitalRead(eight) == LOW) {                             // Reads each switch one at a time
        timeZone += 8;
    }
    if(digitalRead(four) == LOW) {
        timeZone += 4;
    }
    if(digitalRead(two) == LOW) {
        timeZone += 2;
    }
    if(digitalRead(one) == LOW) {
        timeZone += 1;
    }
    if(digitalRead(plusMinus) == HIGH){                                             
        timeZone *= -1;
    }

    if(digitalRead(dst) == LOW) {                               // Reads dip switch 1 to add an hour for daylight savings time
        timeZone++;
    }

    return;
}
