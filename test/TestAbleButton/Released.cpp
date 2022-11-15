/**
 * @file Released.cpp Definition of the on-released callback function. This
 * function performs some assertions on the state of the button list and the
 * individual button pressed when a button is released.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

/**
 * Callback function for button released.
 * 
 * @param btn The button generaing the event.
 */
void onReleased(Button *btn) {
  assert(btnList.allPressed() == false);
  assert(btnList.anyPressed() == false);
  assert(btnList.anyClicked() == true);
  if(btn) {
    assert(btn->isPressed() == false);
    assert(btn->isClicked() == true);
    anyReleased = true;
  } else {
    assert(false);
  }
}
