/**
 * @file TestAbleButton.ino Test the Arduino Button Library Extension (ABLE).
 * This program will periodically output "Looking OK..." to the Serial port. As
 * you press buttons connected to pins 2 and 3 it will assert the button
 * settings in the callback fuctions and in the main loop.
 * 
 * The TestAbleButton program is split (by design) into multiple files to ensure
 * AbleButtons works in multi-module programs. A common Config.h header file
 * declares common elements shared across these modules.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "Config.h"
#include "Checks.h"
#include "Utils.h"

#if TESTABLE_CALLBACK
#include "Callback.h"
Button btnA(BUTTON_A_PIN, onEvent); ///< Button A
Button btnB(BUTTON_B_PIN, onEvent); ///< Button B
#else
Button btnA(BUTTON_A_PIN); ///< Button A
Button btnB(BUTTON_B_PIN); ///< Button B
#endif

/// Array of buttons for ButtonList.
Button *btns[NUM_BUTTONS] = {
  &btnA,
  &btnB
};
ButtonList btnList(btns); ///< List of buttons.
bool led = false; ///< State of the builtin LED.

/**
 * Setup the PushBtn example. Called once to initialise everything.
 */
void setup() {
  Serial.begin(115200);
  Serial.println(F("\nTestAbleButton: AbleButtons Test Harness.\n"));

  pinMode(LED_BUILTIN, OUTPUT);

  Button::setHeldTime(2500);
  assert(Button::heldTime() == 2500);
  Button::setIdleTime(5000);
  assert(Button::idleTime() == 5000);

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    Button::setClickTime(750);
    assert(Button::clickTime() == 750);
# endif

  btnList.begin(); // Begin buttons in the list (sets pin mode etc).

  for(int i = 0; i < NUM_BUTTONS; ++i) {
    checkButtonSetup(btns[i]); // Check each button setup OK.
  }
  checkButtonListIntegrity(); // Check ButtonList setup OK.
}

/**
 * Control TestAbleButton. Called repeatedly in a loop.
 */
void loop() {
  static unsigned long ms = millis(); ///< Timer to preiodically print OK message.

  if(millis() - ms > 5000) {
    Serial.println(F("Looking OK..."));
    ms = millis();
  }

  btnList.handle(); // Handle features of the buttons (debouncing, clicks & callbacks).

#if TESTABLE_CLASS < TESTABLE_CLICKER
  led = btnList.anyPressed(); // Display pressed activity to LED.
#else
  if(btnList.anyClicked()) { // Display clicked activity to LED.
    led = !led;
  }
#endif
  digitalWrite(LED_BUILTIN, led); // Update the LED.

  checkButtonListIntegrity(); // Check ButtonList::any* and ButtonList::all* states...

  for(int i = 0; i < NUM_BUTTONS; ++i) {
    Button *btn = btns[i];
    ButtonState &state(btnState[i]);

    checkButtonIntegrity(btn, state);

#   if TESTABLE_CALLBACK
      // Check state when button pressed event.
      if(state.wasPressed) {
        checkButtonJustPressed(btn);
        state.wasPressed = false; // Clear most recent callback signal.
      }

      // Check state when button released event.
      if(state.wasReleased) {
        checkButtonJustReleased(btn);
        state.wasReleased = false; // Clear most recent callback signal.
      }

      // Check state when button held event.
      if(state.wasHeld) {
        checkButtonJustHeld(btn);
        state.wasHeld = false; // Clear most recent callback signal.
      }

      // Check state when button idle event.
      if(state.wasIdle) {
        checkButtonJustIdle(btn);
        state.wasIdle = false; // Clear most recent release callback signal.
      }
#   endif

    checkButtonListIntegrity();
    displayButtonChanges(i);
  }

  // Reset clicks/double-clicks and check.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btnList.anyClicked() == btnList.resetClicked());
    assert(btnList.anyClicked() == false);
    checkButtonListIntegrity();
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btnList.anyDoubleClicked() == btnList.resetDoubleClicked());
    assert(btnList.anyDoubleClicked() == false);
    checkButtonListIntegrity();
# endif
}
