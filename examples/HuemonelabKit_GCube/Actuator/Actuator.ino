//기본적인 actuator 예제 입니다.
//터미널을 통해 받은 값에 따라 모터의 속도를 제어 합니다.

#include "HuemonelabKit.h"
// 총 연결된 큐브의 수를 설정 합니다. 
#define GCUBE_TOTAL 2

GCube GCube(10,11,GCUBE_TOTAL);

void setup() 
{
    //큐브의 시리얼 통신은 115200만 사용할 수 있기 때문에 따로 설정 가능하게 하지 않았습니다.
    //큐브연결이 완료된 경우 시리얼모니터를 통해 확일 할 수 있습니다.
  Serial.begin(9600);
  GCube.begin();
}

void loop() {
      if(Serial.available()){
      char c = Serial.read();
      
      if(c == '0'){
        GCube.send_a_cube_speed(0, 100);
      }else if(c == '1'){
        GCube.send_a_cube_speed(1, 100);
      }else if(c == '2'){
        GCube.send_a_cube_speed(0, 50);
      }else if(c == '3'){
        GCube.send_a_cube_speed(1, 50);
      }else if(c == '4'){
        GCube.stop_all_cube_motor(GCUBE_TOTAL);
      }else if(c == '5'){
        GCube.send_multi_cube_speed(GCUBE_TOTAL, 100,100,0,0,0,0,0,0); //G0:100, G1:100, G2....:0
      }
	}
}
