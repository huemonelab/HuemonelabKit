/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_TILT_SENSOR_CPP
#define HUEMONELAB_TILT_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Tilt Sensor 세팅
 * - pinMode 설정
 */
TiltSensor::TiltSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
};

/**
 * Tilt Sensor 값 읽기
 * - digital 값 read
 */
int TiltSensor::read()
{
  return digitalRead(_pin);
};

#endif