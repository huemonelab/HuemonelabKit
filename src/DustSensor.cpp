/* 
 * last updated By HuemoneLab, May 2023
 */

 #ifndef HUEMONELAB_DUST_SENSOR_CPP
 #define HUEMONELAB_DUST_SENSOR_CPP

 #include "HuemonelabKit.h"

/* 
 * DustSensor 세팅
 * - pinMode 설정
 */
DustSensor::DustSensor(uint8_t measurePin, uint8_t ledPin)
{
  pinMode(ledPin, OUTPUT);
  _ledPin = ledPin;
  _measurePin = measurePin;
}

/* 
 * DustSensor 값 읽기
 */
int DustSensor::read()
{
  digitalWrite(_ledPin, LOW);
  delayMicroseconds(_samplingTime);

  float voMeasured = analogRead(_measurePin);
  
  delayMicroseconds(_deltaTime);
  digitalWrite(_ledPin, HIGH);
  delayMicroseconds(_sleepTime);
  
  float calcVoltage = voMeasured*(5.0/1024);
  int dustDensity = (0.17*calcVoltage-0.1)*1000; // (단위: ㎍/m³)
  
  if ( dustDensity < 0 ) 
  {
    dustDensity = 0;
  }

  return dustDensity;
}

#endif