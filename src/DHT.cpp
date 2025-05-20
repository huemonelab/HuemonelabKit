/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_DHT_SENSOR_CPP
#define HUEMONELAB_DHT_SENSOR_CPP

#include "HuemonelabKit.h"

#define MIN_INTERVAL 2000

/*
 * DHT sensor 세팅
 * - pinMode 설정
 */
DHT::DHT(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);

   _maxCycles = microsecondsToClockCycles(1000);  // 1 millisecond timeout for
                                                 // reading pulses from DHT sensor.

  // Using this value makes sure that millis() - lastreadtime will be
  // >= MIN_INTERVAL right away. Note that this assignment wraps around,
  // but so will the subtraction.
  _lastReadTime = -MIN_INTERVAL;
};

/**
 * 
 */
float DHT::readT()
{
  float f = NAN;

  if ( read() ) {
    f = data[2];
  }
  return f;
};

float DHT::readH()
{
  float f = NAN;
  if ( read() ) {
    f = data[0];
  }
  return f;
}

boolean DHT::read()
{
  uint32_t currentTime = millis();

  if ((currentTime - _lastReadTime) < 2000) {
    return _lastResult; // return last correct measurement
  }

  _lastReadTime = currentTime;

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  digitalWrite(_pin, HIGH);
  delay(250);

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(20);

  uint32_t cycles[80];
  {
    InterruptLock lock;

    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);

    pinMode(_pin, INPUT_PULLUP);
    delayMicroseconds(10); 

    if (expectPulse(LOW) == 0) {
      DEBUG_PRINTLN(F("Timeout waiting for start signal low pulse."));
      _lastResult = false;
      return _lastResult;
    }
    if (expectPulse(HIGH) == 0) {
      DEBUG_PRINTLN(F("Timeout waiting for start signal high pulse."));
      _lastResult = false;
      return _lastResult;
    }

    for (int i=0; i<80; i+=2) {
      cycles[i]   = expectPulse(LOW);
      cycles[i+1] = expectPulse(HIGH);
    }
  } 

  for (int i=0; i<40; ++i) {
    uint32_t lowCycles  = cycles[2*i];
    uint32_t highCycles = cycles[2*i+1];
    if ((lowCycles == 0) || (highCycles == 0)) {
      DEBUG_PRINTLN(F("Timeout waiting for pulse."));
      _lastResult = false;
      return _lastResult;
    }
    data[i/8] <<= 1;

    if (highCycles > lowCycles) {
      data[i/8] |= 1;
    }
  }

  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    _lastResult = true;
    return _lastResult;
  }
  else {
    DEBUG_PRINTLN(F("Checksum failure!"));
    _lastResult = false;
    return _lastResult;
  }
}

uint32_t DHT::expectPulse(bool level) 
{
  uint32_t count = 0;

  while (digitalRead(_pin) == level) {
    if (count++ >= _maxCycles) {
      return 0; // Exceeded timeout, fail.
    }
  }

  return count;
}

#endif