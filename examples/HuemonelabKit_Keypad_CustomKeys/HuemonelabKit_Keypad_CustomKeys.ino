#include <HuemonelabKit.h>

Keypad keypad;

char keys[4][4] = {
 {'*', '0', '#', 'D'},
 {'7', '8', '9', 'C'},
 {'1', '2', '3', 'A'},  
 {'4', '5', '6', 'B'},  
};

void setup() {
 keypad.setKeys(keys);
 Serial.begin(9600);
}
 
void loop(){
 char key = keypad.getKey();
 if ( key ) { 
   Serial.println(key);
 }
}