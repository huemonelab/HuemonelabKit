/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_SONAR_SENSOR_CPP
#define HUEMONELAB_SONAR_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Sonar sensor 세팅
 * - pinMode 설정
 */
SonarSensor::SonarSensor(uint8_t trig, uint8_t echo)
{
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  _trig = trig;
  _echo = echo;
}

/*
 * Sonar sensor 거리값 읽기
 * - 단위 : cm
 */
float SonarSensor::_getDistance()
{
  /* trig, echo 초기화 */
  digitalWrite(_trig, LOW);
  digitalWrite(_echo, LOW);
  delayMicroseconds(2);

  /* 값 측정 */
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);
  unsigned long duration = pulseIn(_echo, HIGH);

  float value = duration / 29.0 / 2.0; // duration을 거리(cm)로 환산
  return value;
}

float SonarSensor::read()
{
  float value = _getDistance();
  if ( value > 200 || value < 2 ) return ;  // if value is out of limit(2~200cm) return null value
  return value;
}

#endif