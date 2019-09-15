#include "header/rtc.h"

//sets up the real time clock
RTC_DS3231 rtc;

//RTC time is stored as 24hr UTC time
void setRTCTime() {
    int seconds, minute, hour;

    //turns the GPS on
    gpsOn();

    //gets the time from the GPS
    getGPSTime(seconds, minute, hour);

    //stores the GPS time in the RTC, date is set to the start of UNIX time
    rtc.adjust(DateTime(1970, 1, 1, hour, minute, seconds));

    return;
}

//Pulls the time from the RTC and converts it to
void getRTCTime(int &minute, int &hour) {
    //bool update = true;

    //gets the current time from the RTC
    DateTime now = rtc.now();

    //pulls the RTC time
    minute = now.minute();
    hour = now.hour();

    //converts from UTC to the desired time zone
    hour += TIME_ZONE;

    //checks if the timezone compensated time is outside of 24hr
    if (hour < 0) {
        hour += 24;
    }
    else if (hour > 23) {
        hour -= 24;
    }

    //updates the RTC time at 3am in the set timezone every day
    /*
    if(hour == 3 && minute == 0 && update == true) {
        updateRTC();
        update = false;
    }

    update = true;
    */

    //converts to 12hr format
    #ifdef TWELVE_HOUR
        twelveHour(hour);
    #endif

    return;
}

void updateRTC() {
    int cycleSpeed = 50;
    
    //cycles the display so all digets get used once each day to extend life of the tubes
    cycleDisplay(cycleSpeed);

    //sets the RTC time with the GPS
    setRTCTime();

    return;
}

//converts 24hr time to 12hr time
void twelveHour(int &hour) {
    if (hour == 0) {
        hour = 12;
    }
    else if (hour > 12) {
        hour -= 12;
    }

    return;
}
