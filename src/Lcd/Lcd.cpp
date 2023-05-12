/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_LCD_CPP
#define HUEMONELAB_LCD_CPP

#include "HuemonelabKit.h"
#include <Wire.h>

#define LCD_COLS 16
#define LCD_ROWS 2


// use in setup
lcdAddress::lcdAddress(void)
{
  Wire.begin();
  DEBUG_PRINTER.begin(9600);

  while (!Serial){}

  while(1){
    byte error, address;
    int nDevices;
    DEBUG_PRINTLN("Scanning...");
    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0) {
        DEBUG_PRINT("I2C device found at address 0x");
        if (address<16) { 
          DEBUG_PRINT("0");
        }
        DEBUG_PRINT(address,HEX);
        DEBUG_PRINTLN("  !");
        nDevices++;
      }
      else if (error==4) {
        DEBUG_PRINT("Unknow error at address 0x");
        if (address<16) {
          DEBUG_PRINT("0");
        }
        DEBUG_PRINTLN(address,HEX);
      }    
    }
    if (nDevices == 0) {
      DEBUG_PRINTLN("No I2C devices found\n");
    } else {
      DEBUG_PRINTLN("done\n");
      break;
    }
  }
  

}

void Lcd::begin()
{
  clear();
  init();
  backlight();
  setCursor(0, 0);
}

void Lcd::scrollLeft(unsigned long ms = 300)
{
  scrollDisplayLeft();
  delay(ms);
}

void Lcd::scrollRight(unsigned long ms = 300)
{
  scrollDisplayRight();
  delay(ms);
}


#endif