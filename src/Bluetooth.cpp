/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_BLUETOOTH_CPP
#define HUEMONELAB_BLUETOOTH_CPP

#include "HuemonelabKit.h"

/*
 * Bluetooth 세팅
 * - pinMode 설정
 * - SoftwareSerial 객체 생성
 */
Bluetooth::Bluetooth(uint8_t tx, uint8_t rx) : SoftwareSerial(tx, rx)
{
  _tx = tx;
  _rx = rx;
}

/*
 * Bluetooth 이름 설정 모드
 * - 블루투스와 시리얼통신만 반복하여 AT command를 사용한 이름 세팅을 할 수 있도록.
 */
void Bluetooth::setName()
{
  while (1)
  {
    if (DEBUG_PRINTER.available())
    {
      SoftwareSerial::write(DEBUG_PRINTER.read());
    }
    if (SoftwareSerial::available())
    {
      DEBUG_PRINTER.write(SoftwareSerial::read());
    }
  }
}

/*
 * Bluetooth 시리얼 통신 세팅
 */
void Bluetooth::begin(long speed)
{
  return SoftwareSerial::begin(speed);
}

/*
 * Bluetooth 값 읽기 
 */
int Bluetooth::read()
{
  return SoftwareSerial::read();
}

/*
 * Bluetooth 값 읽기
 * - String 형태로 bluetooth 값 읽기
 */
String Bluetooth::readString()
{
  return SoftwareSerial::readString();
}

/* 
 * SoftwareSerial.h 기본 함수 
 * - 참고: [Software Serial Library](https://www.arduino.cc/en/Reference/softwareSerial)
 */
void Bluetooth::end()
{
  return SoftwareSerial::end();
}

bool Bluetooth::listen()
{
  return SoftwareSerial::listen();
}

bool Bluetooth::isListening()
{
  return SoftwareSerial::isListening();
}

bool Bluetooth::stopListening()
{
  return SoftwareSerial::stopListening();
}

bool Bluetooth::overflow()
{
  return SoftwareSerial::overflow();
}

int Bluetooth::peek()
{
  return SoftwareSerial::peek();
}

size_t Bluetooth::write(uint8_t byte)
{
  return SoftwareSerial::write(byte);
}

int Bluetooth::available()
{
  return SoftwareSerial::available();
}

void Bluetooth::flush()
{
  return SoftwareSerial::flush();
}

#endif