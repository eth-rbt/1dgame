#include "LedControl.h"
#include "FastLED.h"

LedControl::LedControl(int dataPin, int clockPin, int numLeds) {
  leds = new CRGB[numLeds];
  this->numLeds = numLeds;
  FastLED.addLeds<APA102, 9, 8, BGR>(leds, numLeds);
}

void LedControl::setup() {
  Serial.begin(57600);
}

void LedControl::updateColors(String input) {
  if (input.length() > 0) {
    int colorIndices[numLeds];
    int index = 0;
    int startIndex = 0;
    int spaceIndex = input.indexOf(' ');
    while (spaceIndex != -1 && index < numLeds) {
      colorIndices[index++] = input.substring(startIndex, spaceIndex).toInt();
      startIndex = spaceIndex + 1;
      spaceIndex = input.indexOf(' ', startIndex);
    }
    if (index < numLeds) {
      colorIndices[index++] = input.substring(startIndex).toInt();
    }
    
    if (index == numLeds) {
      for (int i = 0; i < numLeds; i++) {
        //Serial.print(colorIndices[i]);
        leds[i].nscale8(200);;
        switch (colorIndices[i]) {
          case 0:
            leds[i] = CRGB(0, 255, 221); // Mint Blue 
            break;
          case 1:
            leds[i] = CRGB(225, 0, 110); //Flamingo Red;
            break;
          case 2:
            leds[i] = CRGB(71, 204, 45); //Cactus Green
            break;
          case 3:
            leds[i] = CRGB(255, 190, 11); //Sunrise Yellow
            break;
          case 4:
            leds[i] = CRGB(142, 61, 255); // Royal Purple
            break;
          case 5:
            leds[i] = CRGB(250, 84, 7); // Sunset Orange
            break;
          case 6:
            leds[i] = CRGB(32, 57, 194); //Azure Blue;
            break;
          case 7:
            leds[i] = CRGB(165, 42, 42); // Brown
            break;
          case 8:
            leds[i] = CRGB::Red;
            break;
          case 9:
            leds[i] = CRGB::Green;
            break;
          case 10:
            leds[i] = CRGB::Black;
            break;
          default:
            break;
        }
      }
      //Serial.print(leds);

      FastLED.show();
    }
  }
}
