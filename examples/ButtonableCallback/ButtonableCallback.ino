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
void buttonableCallback(Button::CALLBACK_EVENT, uint8_t);

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, buttonableCallback); ///< The button to check.

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
 * Callback function for button events.
 * 
 * @param event The event that has occured.
 * @param id The identifier of the button generating the callback (unused in
 *           this example).
 */
void buttonableCallback(Button::CALLBACK_EVENT event, uint8_t id) {
  (void)id; // id is unused.
  
  if(event == Button::PRESSED_EVENT) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
