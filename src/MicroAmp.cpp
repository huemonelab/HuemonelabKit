/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_MICROPHONE_AMPLIFIER_CPP
#define HUEMONELAB_MICROPHONE_AMPLIFIER_CPP

#include "HuemonelabKit.h"

/*
 * Microphone Amplifier 세팅
 * - pin 설정
 */
MicroAmp::MicroAmp(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

/*
 * Microphone Amplifier 값 읽기
 */
float MicroAmp::read(int from = 0, int to = 1023){
  int samplingTime = 50;
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;

  while ( millis() - startMillis < samplingTime ) {
    int value = analogRead(_pin);
    if ( value < 1024 ) {
      if ( value > signalMax ) {
        signalMax = value;
      } else if ( value < signalMin ) {
        signalMin = value;
      }
    }
  }

  peakToPeak = signalMax - signalMin;
  return map(peakToPeak, 0, 1023, from, to);
}


#endif