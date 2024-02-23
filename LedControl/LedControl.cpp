#include "LedControl.h"

LedControl::LedControl(int dataPin, int clockPin, int numLeds) {
  leds = new CRGB[numLeds];
  this->numLeds = numLeds;
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, numLeds);
}

void LedControl::setup() {
  Serial.begin(9600);
}

void LedControl::updateColors(String input) {
  if (input.length() > 0) {
    int colorIndices[NUM_LEDS];
    int index = 0;
    int startIndex = 0;
    int spaceIndex = input.indexOf(' ');
    while (spaceIndex != -1 && index < NUM_LEDS) {
      colorIndices[index++] = input.substring(startIndex, spaceIndex).toInt();
      startIndex = spaceIndex + 1;
      spaceIndex = input.indexOf(' ', startIndex);
    }
    if (index < NUM_LEDS) {
      colorIndices[index++] = input.substring(startIndex).toInt();
    }
    if (index == NUM_LEDS) {
      for (int i = 0; i < NUM_LEDS; i++) {
        switch (colorIndices[i]) {
          case 0:
            leds[i] = CRGB::Green;
            break;
          case 1:
            leds[i] = CRGB::Red;
            break;
          case 2:
            leds[i] = CRGB::Blue;
            break;
          case 3:
            leds[i] = CRGB::Yellow;
            break;
          case 4:
            leds[i] = CRGB(128, 0, 128); // Purple
            break;
          case 5:
            leds[i] = CRGB(255, 165, 0); // Orange
            break;
          case 6:
            leds[i] = CRGB(255, 192, 203); // Pink
            break;
          case 7:
            leds[i] = CRGB(165, 42, 42); // Brown
            break;
          case 8:
            leds[i] = CRGB::Cyan;
            break;
          case 9:
            leds[i] = CRGB::Magenta;
            break;
          case 10:
            leds[i] = CRGB::Black;
            break;
          default:
            break;
        }
      }
      FastLED.show();
    }
  }
}
