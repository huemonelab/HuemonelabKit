/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_KIT_H
#define HUEMONELAB_KIT_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "./DotMatrix/DotMatrix.h"
#include "./Keypad/Keypad.h"

#define DEBUG_PRINTER Serial
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }

/* LED */
class Led
{
public:
  Led(uint8_t pin);          // pin 설정
  void on(int = 255); // Led 켜기
  void off();                // Led 끄기
  void blink(int time);      // Led 켜고 끄기 (time: 간격(ms))

private:
  uint8_t _pin;
};

/* RGB LED */
class RGBLed
{
public:
  RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin); // pin 설정
  void setColor(int r, int g, int b);                        // rgb 색상값 지정
  void touchSwitch(int value);

private:
  int _state;
  uint8_t _redPin;
  uint8_t _greenPin;
  uint8_t _bluePin;
};

/* 터치센서 */
class TouchSensor
{
public:
  TouchSensor(uint8_t pin);                        // pin 설정
  int read();                                      // 터치센서 값 읽기
  int count(int  = 30, int  = 50); // 터치 센서 값 카운트세기(`duration`: 카운트 세는 간격, `maxCount`: 최대 카운트 수 )

private:
  uint8_t _pin;
  int _count;
};

/* 음성감지센서 */
class SoundSensor
{
public:
  SoundSensor(uint8_t pin);      // pin 설정
  int read();                    // 소리감지센서 값 읽기
  int count(int  = 150); // 소리감지 카운트세기(`duration`: 카운트 세는 간격)
  void resetCount();             // 카운트 0으로 reset

private:
  uint8_t _pin;
  int _count;
  int _tuner;
  int _lowValue;
};

/* 초음파센서(거리감지) */
class SonarSensor
{
public:
  SonarSensor(uint8_t trig, uint8_t echo); // pin 설정
  float read();                            // 거리값 읽기(단위: cm)

private:
  uint8_t _trig;
  uint8_t _echo;
  float _getDistance();
};

/* 빛감지센서 */
class LightSensor
{
public:
  LightSensor(uint8_t pin);              // pin 설정
  int read(int  = 0, int = 1023); // 빛감지센서값 읽기(analog)
  int readDigital();                     // 빛감지센서값 읽기(digital)

private:
  uint8_t _pin;
};

/* 먼지센서 */
class DustSensor
{
public:
  DustSensor(uint8_t measurePin, uint8_t ledPin);
  int read();

private:
  uint8_t _measurePin;
  uint8_t _ledPin;

  // time constants to measure
  unsigned int _samplingTime = 280;
  unsigned int _deltaTime = 40;
  unsigned int _sleepTime = 9680;
};

/* 서보모터 */
class ServoMotor : public Servo
{
public:
  ServoMotor();

  uint8_t attach(uint8_t pin); // pin 설정
  void write(int angle);       // 모터 각도 조정

  /* from Servo.h */
  void detach();
  void writeMicroseconds(int angle);
  int read();
  int readMicroseconds();
  bool attached();
};

/* 조이스틱 모듈 */
class JoyStick
{
public:
  JoyStick(uint8_t vrX, uint8_t vrY); // x, y 축 pin 설정
  void attach(uint8_t button);        // 버튼 pin 설정
  int read(char dir);                 // vrx, vry 값 읽기
  int isPushed();                     // 버튼 값 읽기

private:
  uint8_t _vrX;
  uint8_t _vrY;
  uint8_t _button;
};

/* Bluetooth - inheritance: SoftwareSerial */
class Bluetooth : public SoftwareSerial
{
public:
  Bluetooth(uint8_t tx, uint8_t rx); // pin 설정

  void setName();          // 블루투스 이름 설정 모드
  void begin(long speed);  // 블루투스 시리얼 (in `setup`)
  virtual int read();      // 블루투스에서 보내는 값 읽기
  String readString();     // 블루투스에서 보내는 문장(string) 읽기
  virtual int available(); // 블루투스에서 보낸 값이 있는지 감지

  /* from SoftwareSerial.h */
  void end();
  bool listen();
  bool isListening();
  bool stopListening();
  bool overflow();
  int peek();
  virtual size_t write(uint8_t byte);
  virtual void flush();

private:
  uint8_t _tx;
  uint8_t _rx;
};

/* Added - 1 July, 2019
 * Updated - 12 December, 2019 
 *  - Update read function
 * Microphone Amplifier */
class MicroAmp
{
public:
  MicroAmp(uint8_t pin);                   // pin 설정 (analog)
  float read(int  = 0, int = 1023); // read during sampling time

private:
  uint8_t _pin;
};

/*
 * Added - 12 December, 2019
 * Pressure Sensor
 */
class PressureSensor
{
public:
  PressureSensor(uint8_t pin);
  int read(int  = 0, int  = 1023);

private:
  uint8_t _pin;
};

class DHT 
{
public:
  DHT(uint8_t pin);
  float readT();
  float readH();

private:
  boolean read();
  uint32_t expectPulse(bool level);

  uint8_t data[5];
  uint8_t _pin;
  uint32_t _lastReadTime, _maxCycles;  
  bool _lastResult;
};

class InterruptLock {
public:
InterruptLock() {
  noInterrupts();
}
~InterruptLock() {
  interrupts();
}
};

/*
 * Added - 13 April, 2020
 * Tilt Sensor
 */
class TiltSensor
{
public:
  TiltSensor(uint8_t pin);
  int read(); // 기울기 센서 값 읽기

private:
  uint8_t _pin;
};

class Stepper
{
public:
  Stepper(uint8_t pin4, uint8_t pin2, uint8_t pin3, uint8_t pin1);
  void setTimer(int second);
  void setDir(int dir); // 1 = 시계, 0 = 반시계
  void move(long degree);

  // original in Stepper.h
  void setSpeed(long rpm);
  void step(int stepsToMove);

private:
  uint8_t _pin1;
  uint8_t _pin2;
  uint8_t _pin3;
  uint8_t _pin4;

  int _direction; // default is 1 (시계방향)
  unsigned long _delay;
  int _stepNumber;
  unsigned long _lastStepTime;

  void stepMotor(int step);
};

class Buzzer
{
public:
  Buzzer(uint8_t pin);
  void note(char key, unsigned long  = 1000);
  void play(int  = 1, int  = 180);
  void stop();
private:
  uint8_t _pin;
};

class ShockSensor
{
public:
  ShockSensor(uint8_t pin);
  int read();
private:
  uint8_t _pin;
};

#endif