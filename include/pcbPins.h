#ifndef PCBPINS_H
#define PCBPINS_H

//GPS pins
#define gpsSerial Serial3 //RX:PJ0 TX:PJ1
const int gpsCtrl = 30; //PC7

//dimming pins
const int dim = 4; //PG5
const int light = 54; //A0 PF0

//dip switch pins
//time set pins
const int plusMinus = 17; //1 PH0
const int eight = 16; //2 PH1
const int four = 6; //3 PH3
const int two = 7; //4 PH4
const int one = 8; //5 PH5
const int dst = 9; //6 PH6
const int timeMode = 10; //7 PB4
//extra pins allotted for latter potential expansion
const int extra1 = 11; //8 PB5
const int extra2 = 12; //9 PB6
const int extra3 = 13; //10 PB7

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