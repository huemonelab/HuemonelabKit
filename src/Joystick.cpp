/*
 * last updated By HuemoneLab, April 2024
 */

 // envs for joystick
#define JOYSTICK_THRESHOLD_LOW 100
#define JOYSTICK_THRESHOLD_HIGH 900

#ifndef HUEMONELAB_JOYSTICK_CPP
#define HUEMONELAB_JOYSTICK_CPP

#include "HuemonelabKit.h"

/*
 * JoyStick 세팅
 * - vrx, vry 핀 세팅
 */
JoyStick::JoyStick(uint8_t vrX, uint8_t vrY) {
	pinMode(vrX, INPUT);
	pinMode(vrY, INPUT);
	_vrX = vrX;
	_vrY = vrY;
};

/*
 * JoyStick 세팅
 * - 버튼 핀 세팅
 */
void JoyStick::attach(uint8_t button) {
	pinMode(button, INPUT_PULLUP);
	_button = button;
};

/*
 * JoyStick x, y 값 읽기
 */
int JoyStick::read(char dir) {
	if (dir == 'x') return analogRead(_vrX); // x축 값
	else if (dir == 'y') return analogRead(_vrY); // y축 값
	else DEBUG_PRINTLN("read('x') 혹은 read('y')를 입력하세요.");
};

/*
 * JoyStick 버튼 값 읽기
 * - pushed: 1, not pushed: 0
 */
int JoyStick::isPushed() {
	return !digitalRead(_button);
};
/*
 * Joystick 방향 판단
 *
 * 핀 0 1 0
 * 핀 2 0 4
 * 핀 0 3 0
 */
int JoyStick::direction(bool toggle = true) {
	int x = analogRead(_vrX);
	int y = analogRead(_vrY);
	int result = 0;
	if (x > JOYSTICK_THRESHOLD_LOW && x < JOYSTICK_THRESHOLD_HIGH) {
		if (y < JOYSTICK_THRESHOLD_LOW) result = 1;
		else if (y > JOYSTICK_THRESHOLD_HIGH) result = 3;
	}
	else if (y > JOYSTICK_THRESHOLD_LOW && y < JOYSTICK_THRESHOLD_HIGH) {
		if (x > JOYSTICK_THRESHOLD_HIGH) result = 4;
		else if (x < JOYSTICK_THRESHOLD_LOW) result = 2;
	}
	else result = 0;
	if (toggle) {
		if (result == 0) _prev_state = 0;
		else {
			if (result == _prev_state) result = 0;
			else _prev_state = result;
		}
	}
	return result;
}

#endif