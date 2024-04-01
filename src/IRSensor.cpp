/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_IR_SENSOR_CPP
#define HUEMONELAB_IR_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * IR sensor 세팅
 * - pinMode 설정
 */
IRSensor::IRSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}


//* 혼동을 방지하기 위해 LOW <-> HIGH (원래 IR sensor 의 경우 감지 시 LOW )
int IRSensor::read()
{
  if ( digitalRead(_pin) == LOW ) return HIGH;
  return LOW;
}

#endif