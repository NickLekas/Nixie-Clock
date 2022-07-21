#include "settings.h"

void settingsInit() {
    int i;

    for(i = extra1; i <= dst; i++) {
        pinMode(i, INPUT_PULLUP);
    }

    return;
}

void getDST(int &DST) {
    if(digitalRead(dst) == LOW) {
        DST = +1;
    }
    else {
        DST = 0;
    }

    return;
}

void getTimeMode(bool &twelveHr) {
    
    if(digitalRead(timeMode) == LOW) {
        twelveHr = true;
    }
    else {
        twelveHr = false;
    }

    return;
}

void getTimeZone(int &timeZone) {
    
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
    if(digitalRead(plusMinus) == LOW) {
        timeZone *= -1;
    }

    return;
}