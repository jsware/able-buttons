/**
 * @file
 * Example on/off control from a button. The built-in LED lights when a button
 * connected between pin 2 and ground is pressed. Uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <able-buttons.h>

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
BasicButton btn(BUTTON_PIN); ///< The button to check.

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

  if(btn.isPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
