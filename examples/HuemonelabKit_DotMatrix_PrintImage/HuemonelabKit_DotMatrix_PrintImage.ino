#include <HuemonelabKit.h>

// 12 - DIN, 11 - CS, 10 - CLK
DotMatrix dot(12, 11, 10);

byte image[8] = {
    B00100100,
    B00100100,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B00000000
};

void setup() {
}

void loop() {
  dot.printImage(image);
}