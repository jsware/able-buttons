/**
 * @file DebounceCallback.ino Example of toggling an LED using callback
 * functions instead of a clicker. When the button is released (completing a
 * click), the on-released function is called to toggle the LED.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackClickerButton;
using ButtonList = AblePullupCallbackClickerButtonList;

bool led = false; ///< On/off state of the LED.

// Forward declaration of callback function.
void releasedCallback(uint8_t);

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, 0, releasedCallback); ///< The button to check.

/**
 * Setup the ClickedBtn example. Called once to initialise everything.
 */
void setup() {
  btn.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control the ClickedBtn example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();
}

/**
 * Callback function for button released.
 * 
 * @param id The identifier of the button generating the callback (ignored in
 *           this example).)
 */
void releasedCallback(uint8_t id) {
  led = !led;
  digitalWrite(LED_BUILTIN, led);
}
