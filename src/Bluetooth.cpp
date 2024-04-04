/* 
 * last updated By HuemoneLab, April 2024
 * 
 * Dependency : SoftwareSerial by Arduino
 */

#ifndef HUEMONELAB_BLUETOOTH_CPP
#define HUEMONELAB_BLUETOOTH_CPP

#include "HuemonelabKit.h"

/*
 * Bluetooth 세팅
 * - pinMode 설정
 * - SoftwareSerial 객체 생성
 */
Bluetooth::Bluetooth(uint8_t tx, uint8_t rx) {
  _tx = tx;
  _rx = rx;
  _serial = new SoftwareSerial(tx, rx);
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
      _serial->write(DEBUG_PRINTER.read());
    }
    if (_serial->available())
    {
      DEBUG_PRINTER.write(_serial->read());
    }
  }
}

/*
 * Bluetooth 시리얼 통신 세팅
 */
void Bluetooth::begin(long speed)
{
  return _serial->begin(speed);
}

/*
 * Bluetooth 값 읽기 
 */
int Bluetooth::read()
{
  return _serial->read();
}

/*
 * Bluetooth 값 읽기
 * - String 형태로 bluetooth 값 읽기
 */
String Bluetooth::readString()
{
  return _serial->readString();
}

/* 
 * SoftwareSerial.h 기본 함수 Wrapping
 * - 참고: [Software Serial Library](https://www.arduino.cc/en/Reference/softwareSerial)
 */
void Bluetooth::end()
{
  return _serial->end();
}

bool Bluetooth::listen()
{
  return _serial->listen();
}

bool Bluetooth::isListening()
{
  return _serial->isListening();
}

bool Bluetooth::stopListening()
{
  return _serial->stopListening();
}

bool Bluetooth::overflow()
{
  return _serial->overflow();
}

int Bluetooth::peek()
{
  return _serial->peek();
}

size_t Bluetooth::write(uint8_t byte)
{
  return _serial->write(byte);
}

int Bluetooth::available()
{
  return _serial->available();
}

void Bluetooth::flush()
{
  return _serial->flush();
}

#endif