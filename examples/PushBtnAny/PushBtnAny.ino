/**
 * @file
 * Example on/off control from multiple buttons. The built-in LED lights when
 * any of the buttons are pressed. Each button is connected to a subsequent PIN.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupButton; ///< Using basic pull-up button.
using ButtonList = AblePullupButtonList; ///< Using basic pull-up button list.

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button between this pin and ground.

Button btnA(BUTTON_A_PIN); ///< Primary button.
Button btnB(BUTTON_B_PIN); ///< Secondary button.

/// Array of buttons for ButtonList.
Button *btns[] = {
  &btnA,
  &btnB
};
ButtonList btnList(btns); ///< List of button to control together.

/**
 * Setup the PushBtn example. Called once to initialise everything.
 */
void setup() {
  btnList.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the PushBtn example. Called repeatedly in a loop.
 */
void loop() {
  btnList.handle();

  if(btnList.anyPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
