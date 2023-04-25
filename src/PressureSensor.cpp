/* 
 * Updated By HuemoneLab, April 2019
 * 
 * PressureSensor.cpp - Library for Educational Arduino Kit made by Huemone Lab.
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

#ifndef HUEMONELAB_TOUCH_SENSOR_CPP
#define HUEMONELAB_TOUCH_SENSOR_CPP

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