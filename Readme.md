This is the initial code for an Arduino Uno based Nixie tube based clock. 

This clock consists of a GPS module to set time and a DS3231SN RTC to keep track of time.

On startup, the gps module will get the current time and send it to the RTC. Once the RTC has the time, the GPS module will be powerd down.

Every night at 3am, the GPS will be turned back on and send the time to RTC. While the DS3231SN is a very precise RTC, this is done just for good measure and there is a chace that the GPS will not be able to aquire time each night.