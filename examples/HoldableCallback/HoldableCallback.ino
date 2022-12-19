/**
 * @file HoldableCallback.ino Example delay timer control using callbacks.
 * 
 * The built-in LED lights up when a button connected between pin 2 and
 * ground is held down for 2 seconds or more. It uses the internal pull-up
 * resistor within an Arduino for the simplest button connection.
 * 
 * When the button is released, the LED stays on, waiting until idle after 5
 * seconds and the LED goes off. Simulates a delay timer.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackButton; ///< Using pull-up button with callbacks.
using ButtonList = AblePullupCallbackButtonList; ///< ButtonList for the same.

// Forward declaration of callback function.
void holdableCallback(Button::CALLBACK_EVENT, uint8_t);

#define BUTTON_PIN 2 ///< Connect button between this pin and ground.
Button btn(BUTTON_PIN, holdableCallback); ///< The button to check.

/**
 * Setup the Debouncable example. Called once to initialise everything.
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Button::setHeldTime(2000);
  Button::setIdleTime(5000);
  
  btn.begin();
}

/**
 * Control the Debouncable example. Called repeatedly in a loop.
 */
void loop() {
  btn.handle();
}

/**
 * Callback function for button events.
 * 
 * @param event The event that has occured.
 * @param id The identifier of the button generating the callback (ignored in this example).
 */
void holdableCallback(Button::CALLBACK_EVENT event, uint8_t id) {
  (void)id; // id is unused.

  if(event == Button::HELD_EVENT) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if(event == Button::IDLE_EVENT) {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
