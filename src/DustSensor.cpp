/* 
 * Updated By HuemoneLab, July 2019
 * 
 * DustSensor.cpp - Library for Educational Arduino Kit made by Huemone Lab.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This software is provided "AS IS" only for educational purpose using MAKER'S BOX Kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.
 * 
 * 본 라이브러리는 (주)휴몬랩이 제작한 메이커스 박스 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 * 
 * Copyright (c) 2019 Huemone Lab Co., Ltd - All Rights Reserved. *
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