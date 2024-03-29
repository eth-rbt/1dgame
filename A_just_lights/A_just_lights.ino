#include "FastLED.h"

#define NUM_LEDS 5
#define DATA_PIN 5
#define CLOCK_PIN 4

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read the input until newline character
    
    // Parse the input
    int colorIndices[NUM_LEDS];
    int index = 0;
    int startIndex = 0; // Start index for substring extraction
    int spaceIndex = input.indexOf(' '); // Find the first space
    while (spaceIndex != -1 && index < NUM_LEDS) {
      colorIndices[index++] = input.substring(startIndex, spaceIndex).toInt();
      startIndex = spaceIndex + 1;
      spaceIndex = input.indexOf(' ', startIndex);
    }
    
    // Extract the last color index (or the only one if there's only one)
    if (index < NUM_LEDS) {
      colorIndices[index++] = input.substring(startIndex).toInt();
    }
    
    // Check if the correct number of color indices are provided
    if (index == NUM_LEDS) {
      // Set colors for all LEDs
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
      FastLED.show(); // Display the changes
    }
  }
}
