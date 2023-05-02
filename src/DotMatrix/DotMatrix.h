/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_DOT_MATRIX_H
#define HUEMONELAB_DOT_MATRIX_H

#pragma once

#include "Arduino.h"
#include <SPI.h>
#include "./MD_Parola/MD_Parola.h"

enum textEffect
{
  left = PA_SCROLL_LEFT,
  right = PA_SCROLL_RIGHT
};

class DotMatrix: public MD_Parola
{
public:
  DotMatrix(uint8_t dataPin, uint8_t csPin, uint8_t clkPin, uint8_t numDevices = 1); 
  void clear();
  
  void printScroll(const char *pText, textEffect effect = left);
  void printImage(const byte images[8]);
  void printEmoji(int num);

private:
  uint8_t _dataPin;
  uint8_t _csPin;
  uint8_t _clkPin;
};

#endif