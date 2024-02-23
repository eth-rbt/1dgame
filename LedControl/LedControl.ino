#include "LedControl.h"

#define DATA_PIN 5
#define CLOCK_PIN 4
#define NUM_LEDS 5

LedControl ledControl(DATA_PIN, CLOCK_PIN, NUM_LEDS);

void setup() {
  ledControl.setup();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    ledControl.updateColors(input);
  }
}
