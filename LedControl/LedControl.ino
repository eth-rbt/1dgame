#include "LedControl.h"

#define dataPin 5
#define clockPin 4
int numLeds= 5;

LedControl ledControl(dataPin, clockPin, numLeds);

void setup() {
  ledControl.setup();
}

void loop() {
  
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    //Serial.print(input);
    ledControl.updateColors(input);
  }
  //Serial.print(ledControl.numLeds);
  //Serial.print(ledControl.leds);
  //FastLED.show();
}
