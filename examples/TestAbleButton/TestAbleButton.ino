/**
 * @file TestAbleButton.ino Test the Arduino Button Library Extension (ABLE).
 * This program will periodically output "Looping..." to the Serial port. As you
 * press buttons connected to pins 2 and 3 it will assert the button settings
 * in the callback fuctions and in the main loop.
 * 
 * The TestAbleButton program is split (by design) into multiple files to ensure
 * ABLE works in multi-module programs. A common TestAbleButton.h header file
 * declares common elements shared across these modules.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

Button btnA(BUTTON_A_PIN, onEvent); ///< Button A
Button btnB(BUTTON_B_PIN, onEvent); ///< Button B

/// Array of buttons for ButtonList.
Button *btns[] = {
  &btnA,
  &btnB
};
ButtonList btnList(btns); ///< List of buttons.

bool anyReleased; ///< Flag indicating releasedCallback was called.
bool led = false; ///< State of the builtin LED.

/**
 * Setup the PushBtn example. Called once to initialise everything.
 */
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Button::setHeldTime(2500);
  Button::setIdleTime(2500);
  
  btnList.begin(); // Begin buttons in the list (sets pin mode etc).
}

/**
 * Control TestButton. Called repeatedly in a loop.
 */
void loop() {
  static uint16_t count = 0; ///< Counter to preiodically print OK message.
  if(!count++) Serial.println(F("Looking OK..."));

  btnList.handle(); // Handle features of the buttons (debouncing, clicks & callbacks).

  if(btnList.anyClicked()) {
    led = !led;
  }

  if(anyReleased) {
    assert(btnList.allPressed() == false);
    // assert(btnList.anyPressed() == true);
    // assert(btnList.allHeld() == false);
    // assert(btnList.anyHeld() == true);
    // assert(btnList.allIdle() == false);
    // assert(btnList.anyIdle() == false);
    assert(btnList.allClicked() == false); // Not all buttons should be clicked.
    assert(btnList.anyClicked() == true); // Clicked will be set after button released.
    assert(btnList.resetClicked() == true); // Clear any clicked status.
    assert(btnList.anyClicked() == false); // No buttons should be clicked now.
    anyReleased = false; // Handled most recent release callback signal.
  } else {
    assert(btnList.allPressed() == false);
    // assert(btnList.anyPressed() == true);
    // assert(btnList.allHeld() == false);
    // assert(btnList.anyHeld() == true);
    // assert(btnList.allIdle() == false);
    // assert(btnList.anyIdle() == false);
    assert(btnList.allClicked() == false);
    assert(btnList.anyClicked() == false);
  }

  digitalWrite(LED_BUILTIN, led);
}