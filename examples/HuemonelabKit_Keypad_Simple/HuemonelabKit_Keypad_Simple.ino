#include <HuemonelabKit.h>

Keypad keypad; // 기본 값 : r1~4 {9,8,7,6}, c1~4 {5,4,3,2}

void setup() {
 Serial.begin(9600);
}

void loop() {
 char key = keypad.getKey();
 if ( key ) {
   Serial.println(key);
 }
}