/*
 * last updated By HuemoneLab, April 2024
 * 
 * Dependency : DallasTemprature by Miles Burton, Tim Newsome, Guli Barros, Rob Tillaart
 */

#ifndef HUEMONELAB_WIRE_TEMP_SENSOR_CPP
#define HUEMONELAB_WIRE_TEMP_SENSOR_CPP

#pragma once

#include "HuemonelabKit.h"

WireTempSensor::WireTempSensor(uint8_t pin)
{
  _oneWire = OneWire(pin);
  _dallasTemp = DallasTemperature(&_oneWire);

  _dallasTemp.begin();
};

float WireTempSensor::read()
{
  _dallasTemp.requestTemperatures();
  return _dallasTemp.getTempCByIndex(0);
};



#endif