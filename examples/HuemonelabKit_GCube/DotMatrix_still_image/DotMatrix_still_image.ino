//Dot Matrix의 Still image예제 입니다.

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
    //1번 큐브에 roll_Image를 업로드 합니다.
    //!0번 큐브에는 메트릭스를 사용 할 수 없습니다.
    GCube.send_matrix_still_image(1, roll_Image);
}
