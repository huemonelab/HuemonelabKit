/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_JOYSTICK_CPP
#define HUEMONELAB_JOYSTICK_CPP

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