#include "rtc.h"

//sets up the real time clock
RTC_DS3231 rtc;

//enables the RTC and checks for power loss
//if there is power loss, sets time using the GPS
//if no power loss, useses last know time and will be updated at 3am local time
void RTCInit() {
    rtc.begin();

    if(rtc.lostPower()) {
        Serial.println("power loss");
        setRTCTime();
    }

    return;
}

//RTC time is stored as 24hr UTC time
void setRTCTime() {
    int seconds, minute, hour;

    //
    gpsInit();

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
    int timeZone;

    //gets the current time from the RTC
    DateTime now = rtc.now();

    //pulls the RTC time
    minute = now.minute();
    hour = now.hour();

    readSettings(timeZone);

    hour += timeZone;

    //checks if the timezone compensated time is outside of 24hr
    if(hour < 0) {
        hour += 24;
    }
    else if(hour > 23) {
        hour -= 24;
    }

    if(digitalRead(timeMode) == LOW) {
        twelveHour(hour);
    }

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
    if(hour == 0) {
        hour = 12;
    }
    else if(hour > 12) {
        hour -= 12;
    }

    return;
}

void readSettings(int &timeZone) {
    //reads dip switch 1-5 as signed binary to calculate the time zone
    if(digitalRead(plusMinus) == HIGH){
        timeZone += -16;
    }
    if(digitalRead(eight) == LOW) {
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
  
    //reads dip dwitch 6 to enable or disable daylight savings mode
    if(digitalRead(dst) == LOW) {
        timeZone++;
    }

    return;
}
