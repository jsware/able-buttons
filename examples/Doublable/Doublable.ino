/**
 * @file Doublable.ino Example toggle control from an Able button.
 * 
 * The built-in LED toggles on/off when a button connected between pin 2 and
 * ground is double-clicked. It uses the internal pull-up resistor within an
 * Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupDoubleClickerButton; ///< Using double-clicker pull-up button.
using ButtonList = AblePullupDoubleClickerButtonList; ///< Using double-clicker pull-up button list.

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN); ///< The button to check.
bool led = false; ///< On/off state of the LED.

/**
 * Setup the Debouncable example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the Debouncable example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();

  // resetDoubleClicked() clears the double-click, returning if the button was
  // double-clicked. It resets the double-click, so it only returns true once
  // per double-click.
  if(btn.resetDoubleClicked()) {
    led = !led;
    digitalWrite(LED_BUILTIN, led);
  }
}
