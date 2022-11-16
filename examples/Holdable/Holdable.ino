/**
 * @file Holdable.ino Example button hold control from an Able button.
 * 
 * The built-in LED lights up when a button connected between pin 2 and
 * ground is held down for 2 seconds or more. It uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupButton; ///< Using basic pull-up button.
using ButtonList = AblePullupButtonList; ///< Using basic pull-up button list.

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN); ///< The button to check.

/**
 * Setup the Debouncable example. Called once to initialise everything.
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Button::setHeldTime(2000);
  Button::setIdleTime(10000);
  
  btn.begin();
}

/**
 * Control the Debouncable example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();

  digitalWrite(LED_BUILTIN, btn.isHeld());
}
