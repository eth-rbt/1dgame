// The EZ Bomb
// Constants don't change
const long holdThreshold = 1000; // Adjust this threshold as needed (in milliseconds)

// Variables will change:
const int numButtons = 5;
const int buttonPins[numButtons] = {6, 5, 4, 3, 2}; // Pins for the buttons, rearranged order
unsigned long buttonPressStartTime[numButtons] = {0}; // Array to store the time when button press starts
bool holdPrinted[numButtons] = {false}; // Array to track if hold message has been printed
//char buttonChars[numButtons] = {'q', 'w', 'e', 'r', 't'};
char buttonChars[numButtons] = {'y', 'u', 'i', 'o', 'p'};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < numButtons; ++i) {
    pinMode(buttonPins[i], INPUT);
  }
}

void loop() {
  // Variable to track if any button state changed
  bool stateChanged = false;

  // Check each button
  for (int i = 0; i < numButtons; ++i) {
    int buttonState = digitalRead(buttonPins[i]);
    //Serial.print("hi");
    if (buttonState == HIGH) {
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


  // Print characters if state changed
  if (stateChanged) {
    for (int i = 0; i < numButtons; ++i) {
      if (digitalRead(buttonPins[i]) == HIGH && !holdPrinted[i]) {
        Serial.print(buttonChars[i]); // Print assigned character for each button
        delay(200);
        Serial.println();
      } else if (holdPrinted[i]) {
        // Handle long press differently if needed
        // For example, print uppercase or a different character
        // Serial.print(toupper(buttonChars[i])); // Example modification
      }
    }
    Serial.println(); // Ensure output is on a new line
  }
}
