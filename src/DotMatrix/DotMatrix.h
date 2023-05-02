#ifndef HUEMONELAB_DOT_MATRIX_H
#define HUEMONELAB_DOT_MATRIX_H

#pragma once

#include "Arduino.h"
#include <SPI.h>
#include "./MD_Parola/MD_Parola.h"

class DotMatrix: public MD_Parola
{
public:
  DotMatrix(uint8_t dataPin, uint8_t clkPin, uint8_t csPin, uint8_t numDevices = 1); 
  
};

#endif