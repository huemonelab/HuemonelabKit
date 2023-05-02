#include <HuemonelabKit.h>

// 12 - DIN, 11 - CS, 10 - CLK
DotMatrix dot(12, 11, 10);

void setup() {
}

void loop() {
  dot.print("A");
  delay(1000);
  dot.print(3);
  delay(1000);
}