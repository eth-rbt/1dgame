#include "EZBomb.h"

EZBomb::EZBomb()
{
    // Initialize arrays here if needed or in the setup function
    int tempButtonPins[numButtons] = {6, 5, 4, 3, 2};
    char tempButtonChars[numButtons] = {'q', 'w', 'e', 'r', 't'};
    //char tempButtonChars[numButtons] = {'y', 'u', 'i', 'o', 'p'};
    unsigned long tempDebounceTime[numButtons] = {0,0,0,0,0};  // the last time the output pin was toggled
    
    memcpy(buttonPins, tempButtonPins, sizeof(tempButtonPins));
    memcpy(buttonChars, tempButtonChars, sizeof(tempButtonChars));
    memcpy(debounceTime, tempDebounceTime, sizeof(tempButtonChars));
}

void EZBomb::setup()
{
    Serial.begin(57600);
    for (int i = 0; i < numButtons; ++i) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttonPressStartTime[i] = 0;
        holdPrinted[i] = false;
        lastButtonState[i]=LOW;
    }
}

void EZBomb::loop()
{
    bool stateChanged = false;
    for (int i = 0; i < numButtons; ++i) {
    int buttonState = digitalRead(buttonPins[i]);
    //Serial.print("hi");
    if (buttonState == LOW) {
      if (buttonPressStartTime[i] == 0) {
        // Button has just been pressed
        buttonPressStartTime[i] = millis(); // Record the time of button press
        holdPrinted[i] = false; // Reset holdPrinted flag
        stateChanged = true; // Indicate that button state changed
      } else if (!holdPrinted[i] && millis() - buttonPressStartTime[i] >= holdThreshold) {
        // Button is being held and hold message hasn't been printed yet
        holdPrinted[i] = true; // Set holdPrinted flag to true to indicate that hold message has been printed
        stateChanged = true; // Indicate that button state changed
      }
    } else {
      // Button is not pressed
      if (buttonPressStartTime[i] != 0) {
        // Button was released
        buttonPressStartTime[i] = 0; // Reset button press start time
        stateChanged = true; // Indicate that button state changed
      }
      holdPrinted[i] = false; // Reset holdPrinted flag when button is released
    }
    // Your existing code to handle button press and hold logic
    // (As provided in your question)
  }

    if (stateChanged) {
        for (int i = 0; i < numButtons; ++i) {
            if (digitalRead(buttonPins[i]) == LOW && !holdPrinted[i]) {
                Serial.println(buttonChars[i]);
                delay(300); // Consider removing or reducing delay for responsiveness
                //Serial.println();
            }
        }
    }
}

void EZBomb::resetButtonState(int index)
{
    buttonPressStartTime[index] = 0;
    holdPrinted[index] = false;
}
