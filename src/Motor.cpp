/*
 * last updated By HuemoneLab, 23 February 2024
 */


#ifndef HUEMONELAB_MOTOR_CPP
#define HUEMONELAB_MOTOR_CPP

#include "HuemonelabKit.h"

Motor::Motor(uint8_t LN1, uint8_t LN2) {
    pinMode(LN1, OUTPUT);
    pinMode(LN2, OUTPUT);
    _LN1 = LN1;
    _LN2 = LN2;
}

void Motor::on(int dir = 0, int ms = 3000) {
    if (dir == 0) {
        digitalWrite(_LN1, HIGH);
        digitalWrite(_LN2, LOW);
    }
    else if (dir == 1) {
        digitalWrite(_LN1, LOW);
        digitalWrite(_LN2, HIGH);
    }
    delay(ms);
}

void Motor::off() {
    digitalWrite(_LN1, LOW);
    digitalWrite(_LN2, LOW);
}

#endif