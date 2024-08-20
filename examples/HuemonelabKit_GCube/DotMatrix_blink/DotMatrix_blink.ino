//Dot Matrix의 Blink image예제 입니다.
//현재 기능 구현이 되어있지 않습니다. 추후 업데이트 예정인듯 합니다.

#include "HuemonelabKit.h"
// 총 연결된 큐브의 수를 설정 합니다. 
#define GCUBE_TOTAL 2 

GCube GCube(10,11,GCUBE_TOTAL);

byte roll_Image[] = {
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000,
  B00000000  
};

void setup() 
{
  Serial.begin(9600);
  GCube.begin();
}

void loop() {
  //!현재 기능 구현이 되어있지 않습니다.
    GCube.send_matrix_still_image(1, roll_Image);
    GCube.set_matrix_blink_rate(1,5);
}
