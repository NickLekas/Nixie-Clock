This is the initial code for an Arduino Mega based Nixie tube based clock. 

This clock consists of a GPS module to set time and a DS3231SN RTC to keep track of time.

On startup, the gps module will get the current time and send it to the RTC. Once the RTC has the time, the GPS module will be powerd down to save energy.

Every night at 3am local time, the GPS will be turned back on and update the RTC time. While the DS3231SN is a very precise RTC, this is done for good measure. Depending on the clocks location, it is possible that the gps will not be able to aquire a signal. After 10 minutes of not aquiring a signal, the GPS will be turned off and an attempt to set the time will be made the next day.
