/**
 * @file Buttonable2.ino Example on/off control from a button. Similar to the
 * Buttonable example, except this example uses a debounced pin.
 *
 * NB: All that's changes is the `using Button` and `using ButtonList` lines at
 * the beginning of the program to select debounced reading capability.
 *  
 * The built-in LED lights when a button connected between pin 2 and ground is
 * pressed. It uses the internal pull-up resistor within an Arduino for the
 * simplest button connection.
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
 * Setup the Buttonable2 example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the Buttonable2 example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();

  digitalWrite(LED_BUILTIN, btn.isPressed());
}
