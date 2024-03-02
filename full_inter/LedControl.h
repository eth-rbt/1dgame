#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "Arduino.h"
#include "FastLED.h"

class LedControl {
  public:
    LedControl(int dataPin, int clockPin, int numLeds);
    void setup();
    void updateColors(String input);

  
    CRGB* leds;
    int numLeds;
};

#endif
