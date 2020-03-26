#ifndef PCBPINS_H
#define PCBPINS_H

//GPS pins
#define gpsSerial Serial3 //RX:PJ0 TX:PJ1
const int gpsCtrl = 30; //PC7

//dimming pins
const int dim = 4; //PG5
const int light = A0; //PF0

//dip switch pins
//time set pins
const int plusMinus = 6; //1 PH3
const int eight = 7; //2 PH4
const int four = 8; //3 PH5
const int two = 9; //4 PH6
const int one = 53; //5 PB0
const int dst = 52; //6 PB1
const int timeMode = 51; //7 PB2
//extra pins allotted for latter potential expansion
const int extra1 = 50; //PB3
const int extra2 = 10; //PB4

//digit pins
//minutes ones
const int minOnesA = 35; //PC2
const int minOnesB = 37; //PC0
const int minOnesC = 40; //PG1
const int minOnesD = 36; //PC1
//minutes tens
const int minTensA = 41; //PG0
const int minTensB = 18; //PD3
const int minTensC = 19; //PD2
const int minTensD = 38; //PD7
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