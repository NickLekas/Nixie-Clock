#ifndef MEGAPINS_H
#define MEGAPINS_H

//GPS pins
#define gpsSerial Serial1
const int gpsCtrl = 4;

//dimming pins
const int dim = 2;
const int light = 54; //A0

//dip switch pins
//time set pins
const int plusMinus = 5; //1
const int eight = 6; //2
const int four = 7; //3
const int two = 8; //4
const int one = 9; //5
const int dst = 10; //6
const int timeMode = 11; //7
//extra pins allotted for latter expansion
const int extra1 = 12;
const int extra2 = 13;

//digit pins
//minutes ones
const int minOnesA = 34;
const int minOnesB = 35;
const int minOnesC = 36;
const int minOnesD = 37;
//minutes tens
const int minTensA = 30;
const int minTensB = 31;
const int minTensC = 32;
const int minTensD = 33;
//hours ones
const int hrOnesA = 26;
const int hrOnesB = 27;
const int hrOnesC = 28;
const int hrOnesD = 29;
//hours tens
const int hrTensA = 22;
const int hrTensB = 23;
const int hrTensC = 24;
const int hrTensD = 25;

//RTC
const int rtcInt = 2;

#endif