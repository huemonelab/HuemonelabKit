/* 
 * last updated By HuemoneLab, April 2024
 * 
 */

#ifndef HUEMONELAB_SERVO_MOTOR_CPP
#define HUEMONELAB_SERVO_MOTOR_CPP

#include "HuemonelabKit.h"

/*
 * 서보모터 세팅
 * - Servo.h 객체 생성
 */
ServoMotor::ServoMotor()
{
    _sv = new Servo();
}

/*
 * 서보모터 세팅
 * - 핀 설정
 */
uint8_t ServoMotor::attach(uint8_t pin)
{
  return _sv->attach(pin);
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

  _sv->write(angle);
}

/* 
 * Servo.h 기본 함수 
 * - 참고: [Servo Library](https://www.arduino.cc/en/reference/servo)
 */
void ServoMotor::writeMicroseconds(int angle)
{
    _sv->writeMicroseconds(angle);
}

void ServoMotor::detach()
{
    _sv->detach();
}

int ServoMotor::read()
{
  return _sv->read();
}

int ServoMotor::readMicroseconds()
{
  return _sv->readMicroseconds();
}

bool ServoMotor::attached()
{
  return _sv->attached();
}

#endif