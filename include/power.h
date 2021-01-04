#ifndef POWER_H
#define POWER_H

#include <Wire.h>
#include <SparkFun_STUSB4500.h>

void programPD();     // Sets the 2 PDO voltages and calculates the currents for a given power limit
#endif