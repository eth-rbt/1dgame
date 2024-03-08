#include "EZBomb.h"
#include "LedControl.h"
#include <FastLED.h>

#define NUM_LEDS1 12 // Number of LEDs
#define DATA_PIN 3 // The pin your LEDs are connected to
#define MAX_BRIGHTNESS 20 // Maximum brightness
#define WAVE_PERIOD 5000 // Initial period of the sine wave in milliseconds
#define SPEED_INCREASE 5 // How much to decrease the wave period by, to increase speed

int numLeds= 5;
#define dataPin 9
#define clockPin 8

CRGB leds1[NUM_LEDS1];
unsigned long startTime = 0;
bool startEffect = false;
int wavePeriod = WAVE_PERIOD;
bool ingame=false;

LedControl ledControl(dataPin, clockPin, numLeds);
EZBomb ezBomb;

void setup() {
  ezBomb.setup();
  ledControl.setup();
  Serial.begin(57600); // Start serial communication at 9600 baud
  FastLED.addLeds<APA102, 15, 14, BGR>(leds1, NUM_LEDS1); //D,C
  FastLED.setBrightness(MAX_BRIGHTNESS);// Initialize the LED strip
}

void loop() {
  ezBomb.loop();
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    //Serial.println(command);// Read the incoming command
    if (command == "mid"){
      ingame=false;
      fill_solid(leds1, NUM_LEDS1, CRGB::Yellow);
      FastLED.show();
    } else if (command == "win"){
      ingame=false;
      fill_solid(leds1, NUM_LEDS1, CRGB::Green);
      FastLED.show();
    } else if (command == "explode"){
      ingame=false;
      fill_solid(leds1, NUM_LEDS1, CRGB::Red);
      FastLED.show();
    } else if (command == "start") {
      Serial.println('h');
      ingame=true;
      startTime = millis(); // Reset start time
      wavePeriod = WAVE_PERIOD; // Reset to initial period
    } else {
      ledControl.updateColors(command);
    }    
  }
  if (ingame){
    updateLedEffect();
  }
}

void updateLedEffect() {
  unsigned long currentTime = millis();
  float elapsed = currentTime - startTime;

  // Increase flashing speed over time by decreasing the wave period
  if (wavePeriod > 500) { // Prevent the period from becoming too short
    wavePeriod = WAVE_PERIOD - (elapsed / SPEED_INCREASE);
  }

  // Use sine wave to determine LED state (on or off)
  float radian = (TWO_PI / wavePeriod) * elapsed;
  float sineValue = sin(radian);

  if (sineValue > 0) {
    // Sine wave is positive, turn LEDs on
    fill_solid(leds1, NUM_LEDS1, CRGB::White);
  } else {
    // Sine wave is negative, turn LEDs off
    fill_solid(leds1, NUM_LEDS1, CRGB::Black);
  }

  FastLED.show();
}
