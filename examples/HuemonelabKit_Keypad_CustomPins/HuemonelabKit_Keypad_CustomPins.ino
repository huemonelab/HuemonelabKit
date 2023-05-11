#include <HuemonelabKit.h>

Keypad keypad;

void setup() {
  keypad.setRows(6, 7, 8, 9); // r1~4 순서대로
  keypad.setCols(2, 3, 4, 5); // c1~4 순서대로
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();
  if ( key ) { 
    Serial.println(key);
  }
}