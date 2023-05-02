#include <HuemonelabKit.h>

// 12 - DIN, 11 - CS, 10 - CLK
DotMatrix dot(12, 11, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  dot.printScroll("makermate"); // default = left
  dot.clear();
  dot.printScroll("hello world!", right);
}
