/**
 * @filele-
 * Example clicked callback from a button. The built-in LED lights on/off when a
 * button connected between pin 2 and ground is clicked (pressed and released).
 * Uses the internal pull-up resistor within an Arduino for the simplest button
 * connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <able-buttons.h>

/// Callback function for button clicked.
void clickedCallback(uint8_t id) {
  if(digitalRead(LED_BUILTIN) == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
ClickableButton btn(BUTTON_PIN, clickedCallback); ///< The button to check.

/**
 * Setup the ClickedBtn example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the ClickedBtn example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();
}
