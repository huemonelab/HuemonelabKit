/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_PRESSURE_SENSOR_CPP
#define HUEMONELAB_PRESSURE_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Pressure sensor 세팅
 * - pinMode 설정
 */
PressureSensor::PressureSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

/*
 * Pressure Sensor 값 읽기 
 */
int PressureSensor::read(int from = 0, int to = 1023)
{
  return map(analogRead(_pin), 0, 1023, from, to);
}

#endif