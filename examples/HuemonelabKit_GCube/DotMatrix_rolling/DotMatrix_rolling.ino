//Dot Matrix의 image rolling 예제 입니다.

#include "HuemonelabKit.h"
#include "dotMatrix.h"

// 총 연결된 큐브의 수를 설정 합니다. 
#define GCUBE_TOTAL 3

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
  GCube.send_matrix_still_image(1,full_Image);
  delay(50);
  GCube.send_matrix_still_image(2, full_Image);
  delay(1000);
  GCube.send_matrix_still_image(1, null_Image);
  GCube.send_matrix_still_image(2, null_Image);
  delay(500);

  int duration = 5; // 롤링시간(초) 계속하려면 0
  GCube.start_matrix_roll_image(GCUBE_TOTAL, roll_Image, duration);
}
