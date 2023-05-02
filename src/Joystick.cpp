/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_RGBLED_CPP
#define HUEMONELAB_RGBLED_CPP

#include "HuemonelabKit.h"

/*
 * JoyStick 세팅
 * - vrx, vry 핀 세팅 
 */
JoyStick::JoyStick(uint8_t vrX, uint8_t vrY){
  pinMode(vrX, INPUT);
  pinMode(vrY, INPUT);
  _vrX = vrX;
  _vrY = vrY;
};

/*
 * JoyStick 세팅 
 * - 버튼 핀 세팅
 */
void JoyStick::attach(uint8_t button){
  pinMode(button, INPUT_PULLUP);
  _button = button;
};

/*
 * JoyStick x, y 값 읽기
 */
int JoyStick::read(char dir){
  if ( dir == 'x') return analogRead(_vrX); // x축 값
  else if ( dir == 'y') return analogRead(_vrY); // y축 값
  else DEBUG_PRINTLN("read('x') 혹은 read('y')를 입력하세요.");
};

/*
 * JoyStick 버튼 값 읽기
 * - pushed: 1, not pushed: 0
 */
int JoyStick::isPushed(){
  return !digitalRead(_button);
};

#endif