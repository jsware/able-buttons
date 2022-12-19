/**
 * @file Pressed.cpp Definition of the on-pressed callback function. This
 * function performs some assertions on the state of the button list and the
 * individual button pressed when a button is pressed.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

Button *pressedBtn; ///< Button just pressed.

/**
 * Callback function for button pressed.
 * 
 * @param btn The button generaing the event.
 */
void onPressed(Button *btn) {
  checkButtonListIntegrity();

  if(btn) {
    checkButtonJustPressed(btn);
    checkButtonListJustPressed(btn);

    pressedBtn = btn;
  } else {
    assert(btn != 0);
  }
}

/**
 * Callback function for button held.
 * 
 * @param btn The button generaing the event.
 */
void onHeld(Button *btn) {
  checkButtonListIntegrity();
  if(btn) {
    checkButtonJustHeld(btn);
    checkButtonListJustHeld(btn);
  } else {
    assert(btn != 0);
  }
}
