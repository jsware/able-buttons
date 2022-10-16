/**
 * @filele-
 * Example on/off callback from a button. The built-in LED lights when a button
 * connected between pin 2 and ground is pressed. Uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <able-buttons.h>

/// Callback function for button pressed.
void pressedCallback(uint8_t id) {
  digitalWrite(LED_BUILTIN, HIGH);
}

/// Callback function for button released.
void releasedCallback(uint8_t id) {
    digitalWrite(LED_BUILTIN, LOW);
}

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
CallbackButton btn(BUTTON_PIN, pressedCallback, releasedCallback); ///< The button to check.

/**
 * Setup the PushBtn example. Called once to initialise everything.
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  btn.begin();
}

/**
 * Control the PushBtn example. Called repeatedly in a loop.
 */
void loop() {
  // put your main code here, to run repeatedly:
  btn.handle();
}
