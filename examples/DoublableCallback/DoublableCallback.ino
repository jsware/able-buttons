/**
 * @file DoublableCallback.ino Example of toggling an LED using callback
 * functions instead of a clicker. When the button is single-clicked, the LED
 * will be illuminated. Double-click to turn the LED off.
 * 
 * @copyright Copyright (c) 2024 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackDoubleClickerButton; ///< Using callback pull-up button.
using ButtonList = AblePullupCallbackDoubleClickerButtonList; ///< Using callback pull-up button list.

// Forward declaration of callback function.
void clickedCallback(Button::CALLBACK_EVENT, uint8_t);

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, clickedCallback); ///< The button to check.
bool led = false; ///< On/off state of the LED.

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
 * @param event The event that has occured.
 * @param id The identifier of the button generating the callback (ignored in this example).
 */
void clickedCallback(Button::CALLBACK_EVENT event, uint8_t id) {
  (void)id; // id is unused.

  if(event == Button::SINGLE_CLICKED_EVENT) {
    led = false;
    digitalWrite(LED_BUILTIN, led);
  } else if(event == Button::DOUBLE_CLICKED_EVENT) {
    led = true;
    digitalWrite(LED_BUILTIN, led);
  }
}
