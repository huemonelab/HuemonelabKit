/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_POT_SENSOR_CPP
#define HUEMONELAB_POT_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * PotSensor 세팅
 * - pinMode 설정
 */
PotSensor::PotSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

int PotSensor::read(int from = 0, int to = 1023)
{
  return map(analogRead(_pin), 0, 1023, from, to);
}


#endif