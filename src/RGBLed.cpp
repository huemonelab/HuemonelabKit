/* 
 * Updated By HuemoneLab, April 2019
 * 
 * RGBLed.cpp - Library for Educational Arduino Kit made by Huemone Lab.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This software is provided "AS IS" only for educational purpose using MAKER'S BOX Kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.
 * 
 * 본 라이브러리는 (주)휴몬랩이 제작한 메이커스 박스 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 * 
 * Copyright (c) 2019 Huemone Lab Co., Ltd - All Rights Reserved. *
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