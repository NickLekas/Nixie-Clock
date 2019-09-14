#include <Arduino.h>
#include <PCF8574.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <RTClib.h>

#include <pins.h>
#include <config.h>
#include <time.h>

void getGPSTime(int &seconds, int &minutes, int &hours); //reads the time data from the gps and applies the time zone
void getRTCTime(int &minutes, int &hours); //reads the time data from the RTC
void setRTCTime(); //sets the RTC time using the GPS
void twelveHour(int &hours); //converts the time from 24hr to 12hr
void startup(); //cyles the tubes and displays the current time at the end
void cycleDisplay(int &delaySpeed); //cycles the tubes thorugh all numbers
void nixieDisplayMinutes(int a, int b, int c, int d, int value); //outputs binary to the minutes nixie drivers
void nixieDisplayHours(int a, int b, int c, int d, int value); //outputs binary to the hours nixie drivers

//sets up the PCF8574 GPIO extenders
PCF8574 minutes(0x20);
PCF8574 hours(0x21);

//sets up the real time clock
RTC_DS3231 rtc;

//sets up the gps
SoftwareSerial gpsSerial(gpsTX, gpsRX);
Adafruit_GPS gps(&gpsSerial);

void setup() {
  int i;

  Serial.begin(115200);

  #ifdef GENERAL_DEBUG
    Serial.println("Starting");
  #endif

  //sets all the pins of the PCF8574 I/O expanders to outputs for cntrolling the nixie drivers
  for (i = 0; i < 8; i++)
  {
    minutes.pinMode(i, OUTPUT);
    hours.pinMode(i, OUTPUT);
  }
  minutes.begin();
  hours.begin();

  //sets the display to 0
  nixieDisplayMinutes(onesA, onesB, onesC, onesD, 0);
  nixieDisplayMinutes(tensA, tensB, tensC, tensD, 0);
  nixieDisplayHours(onesA, onesB, onesC, onesD, 0);
  nixieDisplayHours(tensA, tensB, tensC, tensD, 0);

  //sets up the gps in RMC mode and 1Hz refresh
  gps.begin(9600);
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  gps.sendCommand(PGCMD_ANTENNA);

  //gives the gps 1 second to start up
  delay(1000);
}

void loop() {
  int minutes, hours;
  int minOnes, minTens, hourOnes, hourTens;
  int last = -1, loop = 0;

  startup();

  while (true) {
    //pulls time from the RTC
    getRTCTime(minutes, hours);

    //checks if the time has changed from the last time get
    if (last != minutes) {
      //parses the minute data for the tens and ones digits
      minOnes = minutes % 10;
      minTens = (minutes - minOnes) / 10;

      //parses the hour data for the tens and ones digits
      hourOnes = hours % 10;
      hourTens = (hours - hourOnes) / 10;

      //writes the time data out to the minutes gpio expander
      nixieDisplayMinutes(onesA, onesB, onesC, onesD, minOnes);
      nixieDisplayMinutes(tensA, tensB, tensC, tensD, minTens);

      //writes the time data out to the hours gpio expander
      nixieDisplayHours(onesA, onesB, onesC, onesD, hourOnes);
      nixieDisplayHours(tensA, tensB, tensC, tensD, hourTens);

      //prints the time to the serial monitor
      #ifdef TIME_DEBUG
        Serial.print("RTC Time: ");
        Serial.print(hourTens);
        Serial.print(hourOnes);
        Serial.print(":");
        Serial.print(minTens);
        Serial.print(minOnes);
        Serial.print("\n");
      #endif

      //keeps track of the previous minute to compare with the next gps read cycle
      last = minutes;

      //syncs the time updates to be every 60 seconds on the first loop and then sleeps the arduino ~60 seconds
      if(loop < 1){
        loop++;
      }
      else {
        delay(58500);
      }
    }
  }
}

//pulls 24hr UTC time from the GPS satellites
void getGPSTime(int &seconds, int &minutes, int &hours) {
  #ifdef GENERAL_DEBUG
    Serial.println("Waiting for GPS fix");
  #endif

  //checks for new data and loops until a satellite fix is aquired
  do {  
    //reads the most recent date from the gps
    gps.read();

    //checks if new data was received
    if(gps.newNMEAreceived()) {
      //parses the new data
      gps.parse(gps.lastNMEA());
    }

    //prints out the satellite fix data
    #ifdef FIX_DEBUG
      Serial.print("Fix: ");
      Serial.print(gps.fix);
      Serial.print("\n");
    #endif

  } while(gps.fix < 1 && !gps.newNMEAreceived());

  #ifdef GENERAL_DEBUG
    Serial.println("GPS fix found");
  #endif

  //gets the time from the new gps data
  minutes = gps.minute;
  hours = gps.hour;
  seconds = gps.seconds;

  return;
}

//RTC time is stored as 24hr UTC time
void setRTCTime() {
  int seconds, minutes, hours;

  //gets the time from the GPS
  getGPSTime(seconds, minutes, hours);

  //stores the GPS time in the RTC, date is set to the start of UNIX time
  rtc.adjust(DateTime(1970, 1, 1, hours, minutes, seconds));

  return;
}

//Pulls the time from the RTC and converts it to 
void getRTCTime(int &minutes, int &hours) {
  //gets the current time from the RTC
  DateTime now = rtc.now();

  //pulls the RTC time
  minutes = now.minute();
  hours = now.hour();

  //converts from UTC to the desired time zone
  hours += TIME_ZONE;

  //checks if the timezone compensated time is outside of 24hr
  if (hours < 0)
  {
    hours = 24 + hours;
  }
  else if (hours > 23)
  {
    hours = hours - 24;
  }

  //converts to 12hr format
  #ifdef TWELVE_HOUR
    twelveHour(hours);
  #endif

  return;
}

//converts 24hr time to 12hr time
void twelveHour(int &hours) {
  if(hours == 0)
    {
      hours = 12;
    }
    else if(hours > 12)
    {
      hours -= 12;
    }

  return;
}

void startup() {
  int minutes, hours;
  int minOnes, minTens, hourOnes, hourTens;
  int i, delaySpeed = 50;

  //sets the RTC time using the GPS
  setRTCTime();
  //pulls the time from the RTC
  getRTCTime(minutes, hours);

  //cycles through the digits of the tubes for show
  cycleDisplay(delaySpeed);

  //prints the time data
  #ifdef TIME_DEBUG
    Serial.print("Startup: ");
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print("\n");
  #endif

  //parses the minute data for the tens and ones digits
  minOnes = minutes % 10;
  minTens = (minutes - minOnes) / 10;

  //parses the hour data for the tens and ones digits
  hourOnes = hours % 10;
  hourTens = (hours - hourOnes) / 10;

  //cycles trough all the digits until the the correct number is found
  for(i = 0; i < 10; i++) {
    if(i <= minOnes) {
      nixieDisplayMinutes(onesA, onesB, onesC, onesD, i);
    }

    if(i <= minTens) {
      nixieDisplayMinutes(tensA, tensB, tensC, tensD, i);
    }

    if(i <= hourOnes) {
      nixieDisplayHours(onesA, onesB, onesC, onesD, i);
    }

    if(i <= hourTens) {
      nixieDisplayHours(tensA, tensB, tensC, tensD, i);
    }

    delay(delaySpeed);
  }
}

void cycleDisplay(int &delaySpeed) {
  int i, cycle = 0;

  //cycles though all digites in order four times getting slower on each loop
  do {
    for(i = 0; i < 10; i++) {
      nixieDisplayMinutes(onesA, onesB, onesC, onesD, i);
      nixieDisplayMinutes(tensA, tensB, tensC, tensD, i);
      nixieDisplayHours(onesA, onesB, onesC, onesD, i);
      nixieDisplayHours(tensA, tensB, tensC, tensD, i);

      delay(delaySpeed);
    }

    delaySpeed *= 1.25;

    cycle++;
  } while (cycle < 4);

  return;
}

//writes the given value to the minutes gpio expander
void nixieDisplayMinutes(int a, int b, int c, int d, int value) {
  minutes.digitalWrite(d, (value & 0x08) >> 3);
  minutes.digitalWrite(c, (value & 0x04) >> 2);
  minutes.digitalWrite(b, (value & 0x02) >> 1);
  minutes.digitalWrite(a, value & 0x01);

  return;
}

//writes the given value to the hours gpio expandr
void nixieDisplayHours(int a, int b, int c, int d, int value) {
  hours.digitalWrite(d, (value & 0x08) >> 3);
  hours.digitalWrite(c, (value & 0x04) >> 2);
  hours.digitalWrite(b, (value & 0x02) >> 1);
  hours.digitalWrite(a, value & 0x01);

  return;
}
