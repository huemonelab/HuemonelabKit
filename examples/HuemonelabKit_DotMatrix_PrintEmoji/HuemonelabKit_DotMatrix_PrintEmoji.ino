#include <HuemonelabKit.h>

// 12 - DIN, 11 - CS, 10 - CLK
DotMatrix dot(12, 11, 10);

void setup() {
}

void loop() {
  dot.printEmoji(1); // 1~emoji개수
  delay(1000);
  dot.printEmoji(2);
  delay(1000);
}