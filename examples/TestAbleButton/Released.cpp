/**
 * @file Released.cpp Definition of the on-released callback function. This
 * function performs some assertions on the state of the button list and the
 * individual button pressed when a button is released.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

Button *releasedBtn; ///< Button just released.

/**
 * Callback function for button released.
 * 
 * @param btn The button generaing the event.
 */
void onReleased(Button *btn) {
  checkButtonListIntegrity();

  if(btn) {
    checkButtonJustReleased(btn);
    checkButtonListJustReleased(btn);

    releasedBtn = btn;
  } else {
    assert(false);
  }
}

/**
 * Callback function for button idle.
 * 
 * @param btn The button generaing the event.
 */
void onIdle(Button *btn) {
  checkButtonListIntegrity();

  if(btn) {
    checkButtonJustIdle(btn);
    checkButtonListJustIdle(btn);
  } else {
    assert(false);
  }
}
