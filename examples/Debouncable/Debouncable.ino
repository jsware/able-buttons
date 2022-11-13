/**
 * @file Debouncable.ino Example toggle control from an Able button.
 * 
 * This shows how Able can be used to create the same program as the built-in
 * [Debounce example](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce)
 * included with the Arduino IDE.
 * 
 * The built-in LED toggles on/off when a button connected between pin 2 and
 * ground is clicked (pressed, then released). It uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupClickerButton; ///< Using clicker pull-up button.
using ButtonList = AblePullupClickerButtonList; ///< Using clicker pull-up button list.

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

  // resetClicked() clears the click, returning if the button was clicked. It
  // resets the click, so it only returns true once per click.
  if(btn.resetClicked()) {
    led = !led;
    digitalWrite(LED_BUILTIN, led);
  }
}
