/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_SERVO_MOTOR_CPP
#define HUEMONELAB_SERVO_MOTOR_CPP

#include "HuemonelabKit.h"

/*
 * 서보모터 세팅
 * - Servo.h 객체 생성
 */
ServoMotor::ServoMotor() : Servo()
{
}

/*
 * 서보모터 세팅
 * - 핀 설정
 */
uint8_t ServoMotor::attach(uint8_t pin)
{
  return Servo::attach(pin);
}

/*
 * 서보모터 각도 조정
 * - 각도 값 : 0~180 
 *   [주의] 180을 설정할 경우 모터에서 소리가 날 수 있음
 */
void ServoMotor::write(int angle)
{
  if (angle < 0 || angle > 180)
    DEBUG_PRINTLN("모터 각도는 0~180 사이로 설정해주세요."); // 각도가 0~180 이 아닐 경우 오류메세지 출력

  Servo::write(angle);
}

/* 
 * Servo.h 기본 함수 
 * - 참고: [Servo Library](https://www.arduino.cc/en/reference/servo)
 */
void ServoMotor::writeMicroseconds(int angle)
{
  Servo::writeMicroseconds(angle);
}

void ServoMotor::detach()
{
  Servo::detach();
}

int ServoMotor::read()
{
  return Servo::read();
}

int ServoMotor::readMicroseconds()
{
  return Servo::readMicroseconds();
}

bool ServoMotor::attached()
{
  return Servo::attached();
}

#endif