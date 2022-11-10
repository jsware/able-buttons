/**
 * @file
 * Example on/off callback from a button. The built-in LED lights when a button
 * connected between pin 2 and ground is pressed. Uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackButton; ///< Using callback pull-up button.
using ButtonList = AblePullupCallbackButtonList; ///< Using callback pull-up button list.

/**
 * Callback function for button pressed.
 * 
 * @param id The identifier of the button generating the callback.
 */
void pressedCallback(uint8_t id) {
  digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * Callback function for button released.
 * 
 * @param id The identifier of the button generating the callback.
 */
void releasedCallback(uint8_t id) {
    digitalWrite(LED_BUILTIN, LOW);
}

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, pressedCallback, releasedCallback); ///< The button to check.

/**
 * Setup the PushBtnCallback example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the PushBtnCallback example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();
}
