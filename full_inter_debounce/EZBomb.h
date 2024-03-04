#ifndef EZBomb_h
#define EZBomb_h

#include "Arduino.h"

class EZBomb
{
public:
    EZBomb(); // Constructor
    void setup();
    void loop();
private:
    static const int numButtons = 5;
    int buttonPins[numButtons];
    unsigned long buttonPressStartTime[numButtons];
    bool holdPrinted[numButtons];
    char buttonChars[numButtons];
    unsigned long debounceDelay = 50; 
    unsigned long debounceTime[numButtons];
    bool lastButtonState[numButtons];
    bool buttonState[numButtons];
    const long holdThreshold = 1000; // ms
    void resetButtonState(int index);
    unsigned long lastDebounceTime[numButtons]; // <-- Added for debounce
};

#endif
