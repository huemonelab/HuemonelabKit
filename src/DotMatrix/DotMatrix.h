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