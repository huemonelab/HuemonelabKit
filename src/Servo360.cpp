/*
 * last updated By HuemoneLab, March 2024

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
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
    Serial.println("   ");
    Serial.println(val);
    Servo::write(val);
    delay(time);
    //Servo::write(90);
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