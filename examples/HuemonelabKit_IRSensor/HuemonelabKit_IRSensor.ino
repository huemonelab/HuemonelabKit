#include <HuemonelabKit.h>

IRSensor ir(3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = ir.read();
  Serial.println(value);
}