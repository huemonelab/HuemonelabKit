/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_RGBLED_CPP
#define HUEMONELAB_RGBLED_CPP

#include "HuemonelabKit.h"

/* 
 * RGB LED 세팅
 * - pinMode 설정
 */
RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  _state = 0;
}

/* 
 * RGB LED 색상
 * - r, g, b 각각 최소 0 ~ 최대 255까지 설정 가능
 */
void RGBLed::setColor(int r, int g, int b)
{
  if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
    DEBUG_PRINTLN("RGB LED의 색은 0~255 사이로 지정해주세요."); // r, g, b 값이 0~255 사이 값이 아니라면 오류메세지 출력

  analogWrite(_redPin, r);
  analogWrite(_greenPin, g);
  analogWrite(_bluePin, b);
}

void RGBLed::touchSwitch(int value) {
	if (value == 1) {
		if (_state == 0) {
			_state = 1;
		}
		else if (_state == 1) {
			_state = 0;
		}
	}
	if (_state == 1) {
		RGBLed::setColor(255, 255, 255);
	}
	else if (_state == 0) {
		RGBLed::setColor(0, 0, 0);
	}
	delay(300);
}

#endif