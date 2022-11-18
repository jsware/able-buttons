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
 * @param btn The button generaing the event.
 */
void onPressed(Button *btn) {
  assert(btnList.allPressed() == false);
  assert(btnList.anyPressed() == true);
  assert(btnList.allHeld() == false);
  // assert(btnList.anyHeld() == false);
  assert(btnList.allIdle() == false);
  // assert(btnList.anyIdle() == false);
  assert(btnList.allClicked() == false);
  // assert(btnList.anyClicked() == false);

  if(btn) {
    assert(btn->isPressed() == true);
    assert(btn->isHeld() == false);
    assert(btn->isIdle() == false);
    assert(btn->isClicked() == false);
  } else {
    assert(false);
  }
}

/**
 * Callback function for button held.
 * 
 * @param btn The button generaing the event.
 */
void onHeld(Button *btn) {
  assert(btnList.allPressed() == false);
  assert(btnList.anyPressed() == true);
  assert(btnList.allHeld() == false);
  assert(btnList.anyHeld() == true);
  assert(btnList.allIdle() == false);
  // assert(btnList.anyIdle() == false);
  assert(btnList.allClicked() == false);
  // assert(btnList.anyClicked() == false);

  if(btn) {
    assert(btn->isPressed() == true);
    assert(btn->isHeld() == true);
    assert(btn->isIdle() == false);
    assert(btn->isClicked() == false);
  } else {
    assert(false);
  }
}
