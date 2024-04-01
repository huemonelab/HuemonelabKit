/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_SHOCK_SENSOR_CPP
#define HUEMONELAB_SHOCK_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Shock sensor 세팅
 * - pinMode 설정
 */


ShockSensor::ShockSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  callibrate(true); // default value - true
  setCallibrateLevel(high); // default value - high (10)
}

void ShockSensor::callibrate(bool callibrated)
{
  _callibrated = callibrated;
  _count = 0;
}

void ShockSensor::setCallibrateLevel(callibrateLevel level)
{
  _level = level;
}

int ShockSensor::read()
{

  int rawValue = readRaw();

  if ( !_callibrated ) return rawValue;
  
  if ( rawValue == HIGH ) {
    _count++;
  } else {
    _count = 0;
  }

  if ( _count > _level ) return HIGH;
  return LOW;
}

int ShockSensor::readRaw() 
{
  if ( digitalRead(_pin) == LOW ) return HIGH;
  else return LOW;
}

#endif