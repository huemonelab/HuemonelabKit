/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_TOUCH_SENSOR_CPP
#define HUEMONELAB_TOUCH_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Touch sensor 세팅
 * - pinMode 설정
 * - count 변수를 0으로 초기화
 */
TouchSensor::TouchSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _count = 0;
}

/*
 * Touch Sensor 값 읽기 
 */
int TouchSensor::read()
{
  return digitalRead(_pin);
}

/*
 * Touch Sensor 값 카운트 세기
 * - 터치센서 값이 HIGH(1)이면 count 1 증가, LOW(0)이면 count 1 감소
 * - count 최소값 : 0, 최대값: maxCount(maxCount의 default: 50)
 * - count 세는 주기 : duration
 */
int TouchSensor::count(int duration, int maxCount)
{
  int value = digitalRead(_pin);
  if (value)
  {
    _count++;
    if (_count > maxCount) // count가 maxCount보다 크면
      _count = maxCount;   // count를 maxCount로 지정
  }
  else
  {
    _count--;
    if (_count < 0) // count가 0보다 작으면
      _count = 0;   // count를 0으로 지정
  }
  delay(duration); // duration 만큼 delay
  return _count;
}

#endif