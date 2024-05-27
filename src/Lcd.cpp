/*
 * last updated By HuemoneLab, May 2024
 *
 * Dependency : LiquidCrystal I2C by Frank de Brabander
 */

#ifndef HUEMONELAB_LCD_CPP
#define HUEMONELAB_LCD_CPP

#include "HuemonelabKit.h"

 // use in setup
lcdAddress::lcdAddress(void)
{
    Wire.begin();
    DEBUG_PRINTER.begin(9600);

    while (!Serial) {}

    while (1) {
        byte error, address;
        int nDevices;
        DEBUG_PRINTLN("Scanning...");
        nDevices = 0;
        for (address = 1; address < 127; address++) {
            Wire.beginTransmission(address);
            error = Wire.endTransmission();
            if (error == 0) {
                DEBUG_PRINT("I2C device found at address 0x");
                if (address < 16) {
                    DEBUG_PRINT("0");
                }
                DEBUG_PRINT(address, HEX);
                DEBUG_PRINTLN("  !");
                nDevices++;
            }
            else if (error == 4) {
                DEBUG_PRINT("Unknow error at address 0x");
                if (address < 16) {
                    DEBUG_PRINT("0");
                }
                DEBUG_PRINTLN(address, HEX);
            }
        }
        if (nDevices == 0) {
            DEBUG_PRINTLN("No I2C devices found\n");
        }
        else {
            DEBUG_PRINTLN("done\n");
            break;
        }
    }


}

size_t Lcd::write(uint8_t value) {
    write4bits((value & 0xf0) | 1);
    write4bits(((value << 4) & 0xf0) | 1);
    return 1;
}

void Lcd::clear() {
    send(1);
    delayMicroseconds(2000);
}

void Lcd::send(uint8_t value) {
    write4bits(value & 0xf0);
    write4bits((value << 4) & 0xf0);
}

void Lcd::write4bits(uint8_t value) {
    expanderWrite(value);
    expanderWrite(value | 4);
    delayMicroseconds(1);
    expanderWrite(value & -5);
    delayMicroseconds(50);
}

void Lcd::expanderWrite(uint8_t _data) {
    Wire.beginTransmission(_Addr);
    Wire.write((int)(_data) | _backlightval);
    Wire.endTransmission();
}

void Lcd::begin() {
    clear();
    Wire.begin();
    delay(50);
    expanderWrite(_backlightval);
    delay(1000);
    write4bits(48);
    delayMicroseconds(4500);
    write4bits(48);
    delayMicroseconds(4500);
    write4bits(48);
    delayMicroseconds(150);
    write4bits(32);
    send(28);
    send(12);
    clear();
    send(6);
    send(2);
    delayMicroseconds(2000);
    _backlightval = 8;
    expanderWrite(0);
    send(128);
}

void Lcd::backlight() {
    _backlightval = (_backlightval ? 0 : 8);
    expanderWrite(0);
}

void Lcd::setCursor(uint8_t row, uint8_t col) {
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if (row > _rows) row = _rows - 1;
    send(128 | (col + row_offsets[row]));
}

void Lcd::scrollLeft(unsigned long ms = 300) {
    send(24);
    delay(ms);
}

void Lcd::scrollRight(unsigned long ms = 300) {
    send(28);
    delay(ms);
}

void Lcd::screens(int n, int val_1 = 0, int val_2 = 0) {
    setCursor(0, 0);
    switch (n) {
    case 1:
        print("SMART CONTROLLER");
        setCursor(1, 0);
        print("   <--    -->   ");
        break;
    case 2: // 온습도
        print("   Temp   : ");
        print(val_1);
        print(" C");
        setCursor(1, 0);
        print(" Humidity : ");
        print(val_2);
        print("%");
        break;
    case 3: // 토양수분센서
        print(" Soil  Moisture");
        setCursor(1, 0);
        print("  : ");
        print(val_1);
        break;
    case 4: // 조도센서
        print("  Photoresistor");
        setCursor(1, 0);
        print("  : ");
        print(val_1);
        break;
    case 5: // RGB LED
        print("    RGB  LED");
        setCursor(1, 0);
        print("ON(UP)/OFF(DOWN)");
        break;
    case 6: // 5v fan
        print("     5V FAN");
        setCursor(1, 0);
        print("ON(UP)/OFF(DOWN)");
        break;
    case 7: // water pump
        print("   WATER PUMP");
        setCursor(1, 0);
        print("ON(UP)/OFF(DOWN)");
        break;
    }
}

#endif