/*
 * last updated By HuemoneLab, March 2024
 */

#ifndef HUEMONELAB_SERVO_360_CPP
#define HUEMONELAB_SERVO_360_CPP

#include "HuemonelabKit.h"

 /*
  * 서보모터 세팅
  * - Servo.h 객체 생성
  */
Servo360::Servo360() : Servo() {
    _angle = 90;
}

/*
 * 서보모터 세팅
 * - 핀 설정
 */
uint8_t Servo360::attach(uint8_t pin) {
    return Servo::attach(pin);
}

/*
 * 서보모터 작동 코드
 *   [주의] 물리적인 사유로 움직이지 못하는 지점까지 움직이면 삐 소리가 날 수 있음
 */
void Servo360::write(int angle, int time = 0) {
    Servo::write(90);
    int val = angle < _angle ? 80 : (angle > _angle ? 100 : 90);
    Servo::write(val);
    delay(time);
    if (time != 0) Servo::write(90);
    _angle = angle;
}

/*
 * 서보모터를 정지시키는 코드
 */
void Servo360::stop() {
    Servo::write(90);
    _angle = 90;
}

/*
 * 서보모터의 현재 값(정확히는 이전의 입력 값)을 읽어오는 코드
 */

int Servo360::read() {
    return _angle;
}

/*
 * Servo.h 기본 함수
 * - 참고: [Servo Library](https://www.arduino.cc/en/reference/servo)
 */
int Servo360::readMicroseconds() {
    return Servo::readMicroseconds();
}

bool Servo360::attached() {
    return Servo::attached();
}

void Servo360::writeMicroseconds(int angular_speed) {
    Servo::writeMicroseconds(angular_speed);
}


void Servo360::detach() {
    Servo::detach();
}

#endif