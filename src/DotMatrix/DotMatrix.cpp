#ifndef HUEMONELAB_DOT_MATRIX_CPP 
#define HUEMONELAB_DOT_MATRIX_CPP 

#include "./DotMatrix.h"

#define EMOJI_COUNT 2
const byte IMAGES[EMOJI_COUNT][8] = {
  {
    B00100100,
    B00100100,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B00000000
  },
  {
    B11111111,
    B00000000,
    B00000000,
    B00001100,
    B00001100,
    B00000000,
    B00000000,
    B11111111
  }
};


DotMatrix::DotMatrix(uint8_t dataPin, uint8_t csPin, uint8_t clkPin, uint8_t numDevices = 1)
: MD_Parola(MD_MAX72XX::GENERIC_HW, dataPin, clkPin, csPin, numDevices)
{
  begin();
  setTextAlignment(PA_CENTER);
  setSpeedInOut(100, 100);
  setPause(10*getSpeed());

  _dataPin = dataPin;
  _csPin = csPin;
  _clkPin = clkPin;
}

void DotMatrix::clear()
{
  displayClear();
}

void DotMatrix::printScroll(const char *pText, textEffect effect = left)
{
  displayText((char *)pText, PA_CENTER, getSpeed(), getPause(), (textEffect_t) effect);
  while (!displayAnimate()) {}
}

void DotMatrix::printImage(const byte images[8])
{
  byte status[64];
  byte spidata[16];

  for (int row = 0 ; row < ROW_SIZE ; row++ ) {
    for ( int col = 0 ; col < COL_SIZE ; col++ ) {
      // LedControl.cpp - setLed
      bool state = bitRead(images[col], row);
      
      int offset = 0; 
      byte val = B10000000 >> col;

      if ( state ) 
      {
        status[offset + row] = status[offset + row] | val;
      } 
      else
      {
        val = ~val; 
        status[offset + row] = status[offset + row] & val;
      }
      
      // LedControl.cpp - spiTransfer
      // spiTransfer(addr, row+1, status[offset+row])

      byte opcode = row + 1;
      byte data = status[offset + row];

      int maxbytes=1*2;

      for(int i = 0 ; i < maxbytes;i++)
        spidata[i]=(byte)0;

      //put our device data into the array
      spidata[offset+1] = opcode;
      spidata[offset] = data;
      //enable the line 
      digitalWrite(_csPin, LOW);
      //Now shift out the data 
      for(int i=maxbytes;i>0;i--)
          shiftOut(_dataPin, _clkPin, MSBFIRST, spidata[i-1]);
      //latch the data onto the display
      digitalWrite(_csPin, HIGH);
    }
  }
}

void DotMatrix::printEmoji(int num)
{
  if ( num > EMOJI_COUNT || num <= 0 ) 
    return;
  
  printImage( IMAGES[num-1] );

}

#endif