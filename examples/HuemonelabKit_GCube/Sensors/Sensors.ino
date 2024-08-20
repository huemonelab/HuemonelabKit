//internal 센서를 읽는 방식을 안내합니다.
#include "HuemonelabKit.h"
// 총 연결된 큐브의 수를 설정 합니다. 
#define GCUBE_TOTAL 2 

GCube GCube(2,3,GCUBE_TOTAL);

void setup() 
{
//큐브의 시리얼 통신은 115200만 사용할 수 있기 때문에 따로 설정 가능하게 하지 않았습니다.
//큐브연결이 완료된 경우 시리얼모니터를 통해 알려줍니다.
  Serial.begin(9600);
  GCube.begin();
}

void loop() {
    //get_cube_echo_value의 경우 구현은 했으나 외부 센서를 이용하는 것으로 추정됩니다.
    //어떤 값도 받을 수 없었습니다.
    byte echo_data[3];
    int8_t acc_dataX;
    int8_t acc_dataY;
    byte proxi_data;
    byte button_data;

    //0. echo
    GCube.get_cube_echo_value(echo_data);
    Serial.print("echo value[0]:");
    Serial.println(echo_data[0]);
    Serial.print("echo value[1]:");
    Serial.println(echo_data[1]);
    Serial.print("echo value[2]");
    Serial.println(echo_data[2]);

    //1. 1번 큐브의 acc 값을 받아옵니다.
    acc_dataX = GCube.get_cube_accX_value(1);
    Serial.print("acc-X:");
    Serial.println(acc_dataX);
    acc_dataY = GCube.get_cube_accY_value(1);
    Serial.print("acc-Y:");
    Serial.println(acc_dataY);

    //2. 1번 큐브의 proxi 값을 받아옵니다.
    proxi_data = GCube.get_cube_proxi_value(1);
    Serial.print("proxi");
    Serial.println(proxi_data);

    //3. 1번 큐브의 button 값을 받아옵니다.
    button_data = GCube.get_cube_button_value(1);
    Serial.print("button val:");
    Serial.println(button_data);


    Serial.println("-----------------------");
}
