/* 
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */
#ifndef HUEMONELAB_STEPPER_MOTOR_CPP
#define HUEMONELAB_STEPPER_MOTOR_CPP

#include "HuemonelabKit.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

#define SONGS 5

int melody[SONGS][100] = {
  {
    NOTE_E5,3, NOTE_D5,8, NOTE_C5,4, NOTE_D5,4, NOTE_E5,4, NOTE_E5,4, NOTE_E5,2,
    NOTE_D5,4, NOTE_D5,4, NOTE_D5,2, NOTE_E5,4, NOTE_G5,4, NOTE_G5,2,
    NOTE_E5,3, NOTE_D5,8, NOTE_C5,4, NOTE_D5,4, NOTE_E5,4, NOTE_E5,4, NOTE_E5,2,
    NOTE_D5,4, NOTE_D5,4, NOTE_E5,4, NOTE_D5,4, NOTE_C5,1
  },
  {
    // We Wish You a Merry Christmas
    // Score available at https://musescore.com/user/6208766/scores/1497501
    
    NOTE_C5,4, //1
    NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
    NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
    NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
    NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
    NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
    NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
    NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,

    NOTE_F5,2
  },
  {
    // Fur Elise - Ludwig van Beethovem
    NOTE_E5, 8, NOTE_DS5, 8, //1
    NOTE_E5, 8, NOTE_DS5, 8, NOTE_E5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_C5, 8,
    NOTE_A4, -4, NOTE_C4, 8, NOTE_E4, 8, NOTE_A4, 8,
    NOTE_B4, -4, NOTE_E4, 8, NOTE_GS4, 8, NOTE_B4, 8,
    NOTE_C5, 4,  REST, 8, NOTE_E4, 8, NOTE_E5, 8,  NOTE_DS5, 8,
    
    NOTE_E5, 8, NOTE_DS5, 8, NOTE_E5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_C5, 8,//6
    NOTE_A4, -4, NOTE_C4, 8, NOTE_E4, 8, NOTE_A4, 8, 
    NOTE_B4, -4, NOTE_E4, 8, NOTE_C5, 8, NOTE_B4, 8, 
    NOTE_A4 , 2, REST, 4, //9 - 1st ending
  },
  {
    // Super Mario Bros theme
    NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
    NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
    NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
    NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
    NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
    REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
    NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
    NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
    NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
    REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  }, 
  {
    // Dart Vader theme (Imperial March) - Star wars 
    // Score available at https://musescore.com/user/202909/scores/1141521
    // The tenor saxophone part was used
    NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
    NOTE_F5,2, NOTE_C6,2,
    NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
    NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
    NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, REST, 2
  },
};


Buzzer::Buzzer(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
};

void Buzzer::note(char key, unsigned long duration = 1000)
{
  int note = REST;

  switch (key)
  {
    case 'c':
      note = NOTE_C5;
      break;
    case 'd':
      note = NOTE_D5;
      break;
    case 'e':
      note = NOTE_E5;
      break;
    case 'f':
      note = NOTE_F5;
      break;
    case 'g':
      note = NOTE_G5;
      break;
    case 'a':
      note = NOTE_A5;
      break;
    case 'b':
      note = NOTE_B5;
      break;
    case 'C':
      note = NOTE_C6;
      break;
  }

  if ( note != 0 ) {
    tone(_pin, note, duration*0.9);
    delay(duration);
    noTone(_pin);
  }
};

void Buzzer::play(int number = 1, int tempo = 180)
{
  int n = number - 1;
  if ( n >= SONGS || n < 0 ) {
    return;
  }
  DEBUG_PRINTLN("PLAY")

  int notes = sizeof(melody[n]) / sizeof(melody[n][0]) / 2;

  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  for(int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2){
    divider = melody[n][thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    } else {
      return ;
    }

    tone(_pin, melody[n][thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(_pin);
  }
};

void Buzzer::stop()
{
  noTone(_pin);
};

#endif