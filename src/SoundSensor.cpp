/* 
 * Updated By HuemoneLab, April 2019
 * 
 * SoundSensor.cpp - Library for Educational Arduino Kit made by Huemone Lab.
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

#ifndef HUEMONELAB_SOUND_SENSOR_CPP
#define HUEMONELAB_SOUND_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Sound sensor 세팅
 * - pinMode 설정
 * - count를 0으로 초기화
 * - count 조정을 위해 필요한 변수들(tuner, lowValue)을 0으로 초기화
 */
SoundSensor::SoundSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _count = 0;
  _tuner = 0;
  _lowValue = 0;
}

/*
 * Sound sensor 값 읽기
 */
int SoundSensor::read()
{
  return digitalRead(_pin);
}

/*
 * Sound Sensor 값 카운트 세기
 * - 음성이 감지되는 횟수를 카운팅
 *   (연속된 HIGH(1)값이 나오다가 LOW(0)가 되는 순간 count 1 증가)
 * - 연속된 HIGH 값 사이의 일부 LOW 값은 무시
 * - 연속된 HIGH 값은 `tuner`, HIGH 값 사이의 LOw 값은 `lowValue` 변수를 이용하여 조정
 * 
 * - count 세는 주기 : duration(default: 150)
 *   (duration이 작을 수록 카운팅 오류의 발생확률이 높아짐. 즉 연속된 음성을 2번 이상으로 카운팅할 수 있음.)
 */
int SoundSensor::count(int duration)
{
  int value = digitalRead(_pin);
  if (value)
  {
    if (_tuner == 0)
      _tuner++;

    _lowValue = 0;
  }
  else
  {
    if (_lowValue == 0 && _tuner > 0)
      _count++;

    _lowValue++;
    _tuner = 0;
  }
  delay(duration);
  return _count;
}

/*
 * Sound Sensor 값 카운트 reset
 */
void SoundSensor::resetCount()
{
  _count = 0;
  _tuner = 0;
  _lowValue = 0;
}

#endif