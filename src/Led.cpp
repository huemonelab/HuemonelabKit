/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_LED_CPP
#define HUEMONELAB_LED_CPP

#include "HuemonelabKit.h"

/* 
 * LED pinMode 세팅
 * - pinMode 설정
 */
Led::Led(uint8_t pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

/*
 * LED 켜기
 * - PWM 핀의 경우 amount에 따라 세기 조절 가능
 * - 기본 amount 값 : 255
 */
void Led::on(int amount)
{
  if (amount <= 130 &&
      (_pin == 0 || _pin == 1 || _pin == 2 || _pin == 4 || _pin == 7 || _pin == 8 || _pin == 12 || _pin == 13))
    DEBUG_PRINTLN("Led 빛의 크기를 조정하기 위해선 PWM 핀에 연결해야 합니다.");

  analogWrite(_pin, amount);
}

/*
 * LED 끄기
 */
void Led::off()
{
  digitalWrite(_pin, LOW);
}

/*
 * LED 깜박이기
 * - time : 깜빡이는 간격 (ms)
 */
void Led::blink(int time)
{
  digitalWrite(_pin, HIGH);
  delay(time);
  digitalWrite(_pin, LOW);
  delay(time);
}

#endif