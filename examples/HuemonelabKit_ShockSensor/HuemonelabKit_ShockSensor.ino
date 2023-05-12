#include <HuemonelabKit.h>

ShockSensor shock(2);

void setup() {
  Serial.begin(9600);
  // shock.callibrate(false); // callibration option off ( default: true )
  // shock.setCallibrateLevel(low); // callibration level ( option - `high` or `low`). Default value is `high`.
}

void loop() {
  int value = shock.read();
  if ( value == 1 ) {
    Serial.println("shocked");
  } 
}