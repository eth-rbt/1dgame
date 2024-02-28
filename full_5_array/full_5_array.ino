#include "EZBomb.h"
#include "LedControl.h"

int numLeds= 5;
#define dataPin 9
#define clockPin 8

LedControl ledControl(dataPin, clockPin, numLeds);
EZBomb ezBomb;

void setup() {
  ezBomb.setup();
  ledControl.setup();

}

void loop() {
  ezBomb.loop();
  if (Serial.available()) {
    String input = Serial.readStringUntil('/n');
    //Serial.print(input);
    ledControl.updateColors(input);
  }
}
