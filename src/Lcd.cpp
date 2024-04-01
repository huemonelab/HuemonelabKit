/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_LCD_CPP
#define HUEMONELAB_LCD_CPP

#include "HuemonelabKit.h"

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

Lcd::Lcd() {
    _lcd = new LiquidCrystal_I2C(0x00, LCD_COLS, LCD_ROWS);
}

Lcd::Lcd(uint8_t addr) {
    _lcd = new LiquidCrystal_I2C(addr, LCD_COLS, LCD_ROWS);
}

void Lcd::begin()
{
    _lcd->clear();
    _lcd->init();
    _lcd->backlight();
    _lcd->setCursor(0, 0);
}

void Lcd::scrollLeft(unsigned long ms = 300)
{
    _lcd->scrollDisplayLeft();
    delay(ms);
}

void Lcd::scrollRight(unsigned long ms = 300)
{
    _lcd->scrollDisplayRight();
    delay(ms);
}

void Lcd::setCursor(uint8_t row, uint8_t col) {
    _lcd->setCursor(col, row);
}

void Lcd::print(char* pText) {
    _lcd->print(pText);
}

void Lcd::clear() {
    _lcd->clear();
}

void Lcd::backlight() {
    _lcd->backlight();
}

#endif