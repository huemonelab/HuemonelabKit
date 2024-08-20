//기본적인 연결방식을 안내합니다.

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

}
