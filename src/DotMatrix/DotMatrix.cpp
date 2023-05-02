#ifndef HUEMONELAB_DOT_MATRIX_CPP 
#define HUEMONELAB_DOT_MATRIX_CPP 

#include "./DotMatrix.h"

DotMatrix::DotMatrix(uint8_t dataPin, uint8_t clkPin, uint8_t csPin, uint8_t numDevices = 1)
: MD_Parola(MD_MAX72XX::GENERIC_HW, dataPin, clkPin, csPin, numDevices)
{} 

#endif