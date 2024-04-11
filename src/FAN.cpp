/*
 * last updated By HuemoneLab, 05 April 2024
 */


#ifndef HUEMONELAB_FAN_CPP
#define HUEMONELAB_FAN_CPP

#include "HuemonelabKit.h"

 /*
  * 5V FAN 세팅
  * - pinMode 설정
  */
FAN::FAN(uint8_t pin) {
	_pin = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

/*
 * FAN 켜기
 * LOW 값을 넣어줘야 켜짐에 유의
 */
void FAN::on() {
	digitalWrite(_pin, LOW);
}

/*
 * FAN 끄기
 * HIGH 값을 넣어줘야 꺼짐에 유의
 */
void FAN::off() {
	digitalWrite(_pin, HIGH);
}

#endif