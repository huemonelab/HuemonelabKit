/* 
 * last updated By HuemoneLab, May 2023
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