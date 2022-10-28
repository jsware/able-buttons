/**
 * @file
 * Example on/off control from multiple buttons. The built-in LED lights when
 * all of the buttons are pressed. Each button is connected to a subsequent PIN.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <able-buttons.h>

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.

/// Array of buttons.
BasicButton btns[] = {
  BasicButton(BUTTON_PIN),
  BasicButton(BUTTON_PIN + 1)
};
BasicButtonList btnList(btns); ///< List of button to control together.

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
  
  if(btnList.allPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
