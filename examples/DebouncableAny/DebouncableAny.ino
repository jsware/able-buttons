/**
 * @file DebouncableAny.ino Example toggle control from multiple buttons. If any
 * button in the list is clicked, the built-in LED will toggle on/off.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupClickerButton; ///< Using clicker pull-up button.
using ButtonList = AblePullupClickerButtonList; ///< Using clicker pull-up button list.

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button between this pin and ground.

Button btnA(BUTTON_A_PIN); ///< Primary button.
Button btnB(BUTTON_B_PIN); ///< Secondary button.
bool led = false; ///< On/off state of the LED.

/// Array of buttons for ButtonList.
Button *btns[] = {
  &btnA,
  &btnB
};
ButtonList btnList(btns); ///< List of button to control together.

/**
 * Setup the DebouncableAny example. Called once to initialise everything.
 */
void setup() {
  btnList.begin(); // ButtonList calls begin() for each button in the list.
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the DebouncableAny example. Called repeatedly in a loop.
 */
void loop() {
  btnList.handle(); // ButtonList calls handle() for each button in the list.

  // resetClicked() on ButtonList clears clicks on all the buttons in the list,
  // returning if any one of the button was clicked. Resetting the clicks
  // ensures clicks are handled only once.
  if(btnList.resetClicked()) {
    led = !led;
    digitalWrite(LED_BUILTIN, led);
  }
}
