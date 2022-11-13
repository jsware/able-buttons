/**
 * @file Pressed.cpp Definition of the on-pressed callback function. This
 * function performs some assertions on the state of the button list and the
 * individual button pressed when a button is pressed.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

/**
 * Callback function for button pressed.
 * 
 * @param id The identifier of the button generating the callback.
 */
void pressedCallback(uint8_t id) {
  assert(id > 0);
  Button *btn = btnList.button(id); assert(btn == btns[id - 1]);

  assert(btnList.allPressed() == false);

  if(btn) {
    assert(btn->isPressed() == true);
    assert(btn->isClicked() == false);
  } else {
    assert(false);
  }
}
