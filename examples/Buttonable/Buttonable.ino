/**
 * @file Buttonable.ino Example on/off control from an Able button.
 * 
 * This shows how Able can be used to create the same program as the built-in
 * [Button example](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button)
 * included with the Arduino IDE.
 * 
 * The built-in LED lights when a button connected between pin 2 and ground is
 * pressed. It uses the internal pull-up resistor within an Arduino for the
 * simplest button connection.
 * 
 * NB: This example uses direct pin reading which is not debounced. Contact
 * bouncing can make the button's signal unstable for a few ms when pressed or
 * released.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupDirectButton; ///< Using the direct pull-up button.
using ButtonList = AblePullupDirectButtonList; ///< Using the direct pull-up button list.

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN); ///< The button to check.

/**
 * Setup the Buttonable example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the Buttonable example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();

  digitalWrite(LED_BUILTIN, btn.isPressed());
}
