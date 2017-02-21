
#include "KeyPad.h"

KeyPad lock;

void setup() {
  Serial.begin(9600);
  // columns are inputs/ rows are outputs
  DDRD = 15;
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonPress = lock.checkKeyPress();
  if (buttonPress < 10) {
    Serial.print(buttonPress);
    Serial.print("\n");
  }
  else if (buttonPress == 10) {
    Serial.print("*");
    Serial.print("\n");
  }
  else if (buttonPress == 11) {
    Serial.print("0");
    Serial.print("\n");
  }
  else if (buttonPress == 12) {
    Serial.print("#");
    Serial.print("\n");
  }
}