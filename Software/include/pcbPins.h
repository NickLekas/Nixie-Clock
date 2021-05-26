#ifndef PCBPINS_H
#define PCBPINS_H

//GPS pins
#define gpsSerial Serial3 //RX:PJ0 TX:PJ1
const int gpsCtrl = 39; //PG2

//dimming pins
const int dim = 4; //PG5
const int light = 54; //A0 PF0

//dip switch pins
//time set pins
const int dst = 29; //1 PA7
const int timeMode = 28; //2 PA6
const int plusMinus = 27; //3 PA5
const int eight = 26; //4 PA4
const int four = 25; //5 PA3
const int two = 24; //6 PA2
const int one = 23; //7 PA1
//extra pin allotted for latter potential expansion
const int extra1 = 22; //8 PA0

//digit pins
//minutes ones
const int minOnesA = 30; //PC7
const int minOnesB = 32; //PC5
const int minOnesC = 33; //PC4
const int minOnesD = 31; //PC6

//minutes tens
const int minTensA = 34; //PC3
const int minTensB = 36; //PC1
const int minTensC = 37; //PC0
const int minTensD = 35; //PC2

//hours ones
const int hrOnesA = 42; //PL7
const int hrOnesB = 44; //PL5
const int hrOnesC = 45; //PL4
const int hrOnesD = 43; //PL6

//hours tens
const int hrTensA = 46; //PL3
const int hrTensB = 48; //PL1
const int hrTensC = 49; //PL0
const int hrTensD = 47; //PL2

//RTC
const int rtcInt = 2; //PE4

#endif