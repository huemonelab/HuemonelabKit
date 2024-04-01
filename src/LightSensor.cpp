/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_LIGHT_SENSOR_CPP
#define HUEMONELAB_LIGHT_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Light sensor 세팅
 * - pinMode 설정
 */
LightSensor::LightSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

/* 
 * Updated 12, December 2019
 * - Add parameter from and to value and return mapped value
 * Light sensor 값 읽기 (analog) 
 */
int LightSensor::read(int from = 0, int to = 1023)
{
  return map(analogRead(_pin), 0, 1023, from, to);
}

/* 
 * Light sensor 값 읽기 (digital) 
 */
int LightSensor::readDigital()
{
  return digitalRead(_pin);
}

#endif