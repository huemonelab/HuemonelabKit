#include <HuemonelabKit.h>

Lcd lcd(0x27);

void setup() {
  lcd.begin(); // clear, init, backlight, setCursor(0,0)
  lcd.print("hello world");  
}

void loop() {
  lcd.scrollLeft(); // or scrollRight
}