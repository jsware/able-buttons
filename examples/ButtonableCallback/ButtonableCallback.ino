/**
 * @file ButtonableCallback.ino Example on/off button via callback functions.
 * Similar to Buttonable example, but uses on-pressed and on-released callback
 * functions to control the built-in LED.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackButton; ///< Using callback pull-up button.
using ButtonList = AblePullupCallbackButtonList; ///< Using callback pull-up button list.

// Declarations of callback functions defined later.
void pressedCallback(uint8_t);
void releasedCallback(uint8_t);

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, pressedCallback, releasedCallback); ///< The button to check.

/**
 * Setup the ButtonableCallback example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the ButtonableCallback example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();
}

/**
 * Callback function for button pressed.
 * 
 * @param id The identifier of the button generating the callback (unused in
 *           this example).
 */
void pressedCallback(uint8_t id) {
  digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * Callback function for button released.
 * 
 * @param id The identifier of the button generating the callback (unused in
 *           this example).
 */
void releasedCallback(uint8_t id) {
    digitalWrite(LED_BUILTIN, LOW);
}
