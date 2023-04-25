/* 
 * Updated By HuemoneLab, 12 December 2019
 * 
 * SonarSensor.cpp - Library for Educational Arduino Kit made by Huemone Lab.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This software is provided "AS IS" only for educational purpose using MAKER'S BOX Kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.
 * 
 * 본 라이브러리는 (주)휴몬랩이 제작한 메이커스 박스 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 * 
 * Copyright (c) 2019 Huemone Lab Co., Ltd - All Rights Reserved. *
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