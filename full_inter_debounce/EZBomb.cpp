#include "EZBomb.h"

EZBomb::EZBomb()
{
    // Initialize arrays here if needed or in the setup function
    int tempButtonPins[numButtons] = {6, 5, 4, 3, 2};
    char tempButtonChars[numButtons] = {'q', 'w', 'e', 'r', 't'};
    //char tempButtonChars[numButtons] = {'y', 'u', 'i', 'o', 'p'};
    //unsigned long tempDebounceTime[numButtons] = {0,0,0,0,0};  // the last time the output pin was toggled
    
    memcpy(buttonPins, tempButtonPins, sizeof(tempButtonPins));
    memcpy(buttonChars, tempButtonChars, sizeof(tempButtonChars));
    //memcpy(debounceTime, tempDebounceTime, sizeof(tempButtonChars));
}

void EZBomb::setup()
{
    Serial.begin(57600);
    for (int i = 0; i < numButtons; ++i) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttonPressStartTime[i] = 0;
        holdPrinted[i] = false;
        lastButtonState[i]=HIGH;
        buttonState[i]=HIGH;
    }
}

void EZBomb::loop()
{
    bool stateChanged = false;
    for (int i = 0; i < numButtons; ++i) {
      int reading = digitalRead(buttonPins[i]);
      if (reading != lastButtonState[i]) {
        lastDebounceTime[i] = millis();
       }

      if ((millis() - lastDebounceTime[i]) > debounceDelay) {
        // if the button state has changed:
        if (reading != buttonState[i]) {
          buttonState[i] = reading;
          // only toggle the LED if the new button state is HIGH
          if (buttonState[i] == LOW) {
            Serial.println(buttonChars[i]);
          }
        }
      }
      lastButtonState[i] = reading;        
  }             
}

void EZBomb::resetButtonState(int index)
{
    buttonPressStartTime[index] = 0;
    holdPrinted[index] = false;
}
