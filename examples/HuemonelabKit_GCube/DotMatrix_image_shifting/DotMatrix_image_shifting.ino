//Dot Matrix의 image shifting 예제 입니다.
//Acc sensor 값을 받아와서 가속도 값 만큼 이미지를 Shifting 합니다.

#include "HuemonelabKit.h"
#include "dotMatrix.h"

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
  int8_t acc_dataX;
  int8_t acc_dataY;
  acc_dataX = GCube.get_cube_accX_value(0);
  acc_dataY = GCube.get_cube_accY_value(0);

  Serial.print("x: ");
  Serial.print(acc_dataX);
  Serial.print("  y: ");
  Serial.print(acc_dataY);
  Serial.println("");

  // Shift image along the acc data with Sync. all connected GCubes  
  GCube.start_matrix_shift_image(0, GCUBE_TOTAL, roll_Image, acc_dataX, acc_dataY); 
}
