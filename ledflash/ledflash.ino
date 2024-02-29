#include <FastLED.h>

#define NUM_LEDS 6 // Number of LEDs
#define DATA_PIN 3 // The pin your LEDs are connected to
#define MAX_BRIGHTNESS 20 // Maximum brightness
#define WAVE_PERIOD 5000 // Initial period of the sine wave in milliseconds
#define SPEED_INCREASE 10 // How much to decrease the wave period by, to increase speed

CRGB leds[NUM_LEDS];
unsigned long startTime = 0;
bool startEffect = false;
int wavePeriod = WAVE_PERIOD;

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  FastLED.addLeds<APA102, 9, 8, BGR>(leds, NUM_LEDS); 
  FastLED.setBrightness(MAX_BRIGHTNESS);// Initialize the LED strip
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read the incoming command
    if (command == "start") {
      Serial.print('hi');
      startEffect = true;
      startTime = millis(); // Reset start time
      wavePeriod = WAVE_PERIOD; // Reset to initial period
    }
  }

  if (startEffect) {
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
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else {
    // Sine wave is negative, turn LEDs off
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }

  FastLED.show();
}
