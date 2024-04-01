/* 
 * last updated By HuemoneLab, May 2023
 */

#ifndef HUEMONELAB_STEPPER_MOTOR_CPP
#define HUEMONELAB_STEPPER_MOTOR_CPP

#include "HuemonelabKit.h"
#define STEPS 2048

/*
 * DHT sensor 세팅
 * - pinMode 설정
 */
Stepper::Stepper(uint8_t pin4, uint8_t pin2, uint8_t pin3, uint8_t pin1)
{
  _stepNumber = 0;
  _direction = 1;
  _lastStepTime = 0;
  _delay = 60L * 1000L * 1000L / STEPS; // Default - 1 RPM
  
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3; 
  _pin4 = pin4; 
  
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
};



void Stepper::setDir(int direction)
{
  _direction = direction;
};

void Stepper::setTimer(int second)
{
  _delay = second * 1000L * 1000L / STEPS;

  if ( _direction == 1 ) {
    step(STEPS);
  } else {
    step(-STEPS);
  }
};

void Stepper::move(long degree)
{
  int stepsToMove = (int) (STEPS * degree / 360L);
  step(stepsToMove);
};


void Stepper::setSpeed(long rpm)
{
  _delay = 60L * 1000L * 1000L / STEPS / rpm; // In MicroSeconds
};

void Stepper::step(int stepsToMove)
{
  int leftSteps = abs(stepsToMove);

  if ( stepsToMove > 0 ) { _direction = 1; }
  if ( stepsToMove < 0 ) { _direction = 0; }
  
  while ( leftSteps > 0 ) {
    unsigned long now = micros();

    if ( now - _lastStepTime >= _delay ) {
      _lastStepTime = now;

      if ( _direction == 0 ) {
        if ( _stepNumber == STEPS ) {
          _stepNumber = 0;
        }
        _stepNumber++;
      } else {
        if ( _stepNumber == 0 ) {
          _stepNumber = STEPS;
        }
        _stepNumber--;
      }

      leftSteps--;

      stepMotor(_stepNumber % 4);
    }
  }
};

/*
 * Moves the motor forward or backwards.
 */
void Stepper::stepMotor(int step)
{
  switch (step) {
    case 0:  // 1010
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, LOW);
      digitalWrite(_pin3, HIGH);
      digitalWrite(_pin4, LOW);
    break;
    case 1:  // 0110
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, HIGH);
      digitalWrite(_pin3, HIGH);
      digitalWrite(_pin4, LOW);
    break;
    case 2:  //0101
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, HIGH);
      digitalWrite(_pin3, LOW);
      digitalWrite(_pin4, HIGH);
    break;
    case 3:  //1001
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, LOW);
      digitalWrite(_pin3, LOW);
      digitalWrite(_pin4, HIGH);
    break;
  }
};

#endif