/**
 * @file CheckLists.cpp Check the ButtonList::all*() and ButtonList::any().
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

/**
 * Check initial setup of the button list. 
 */
void checkButtonListSetup() {
  // Given the button list, when first setup, then...
  assert(btnList.allPressed() == false); // ...not all pressed.
  assert(btnList.allHeld() == false); // ...not all held.
  assert(btnList.allIdle() == false); // ...not all idle.
#if TESTABLE_CLASS >= TESTABLE_CLICKER
  assert(btnList.allClicked() == false); // ...not all clicked
#endif
#if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
  assert(btnList.allDoubleClicked() == false); // ...not all double-clicked.
#endif

  assert(btnList.anyPressed() == false);
  assert(btnList.anyHeld() == false);
  assert(btnList.anyIdle() == false);
#if TESTABLE_CLASS >= TESTABLE_CLICKER
  assert(btnList.anyClicked() == false);
#endif
#if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
  assert(btnList.anyDoubleClicked() == false);
#endif
}

/**
 * Check ButtonList when button just pressed. 
 */
void checkButtonListJustPressed(Button *btn) {
  // Given the button just pressed, then...
  if(btn == &btnA) {
    assert(btnList.allPressed() == btnB.isPressed()); // ...all pressed if other pressed.
  } else {
    assert(btnList.allPressed() == btnA.isPressed()); // ...all pressed if other pressed.
  }

  assert(btnList.allHeld() == false); // ...cannot all be held.
  assert(btnList.allIdle() == false); // ...cannot all be idle.

  assert(btnList.anyPressed() == true); // ...any pressed is true.

  if(btn == &btnA) {
    assert(btnList.anyHeld() == btnB.isHeld());
    assert(btnList.anyIdle() == btnB.isIdle());
  } else {
    assert(btnList.anyHeld() == btnA.isHeld());
    assert(btnList.anyIdle() == btnA.isIdle());
  }
}

/**
 * Check ButtonList when button just released. 
 */
void checkButtonListJustReleased(Button *btn) {
  // Given the button just released, then...
  assert(btnList.allPressed() == false);
  assert(btnList.allHeld() == false); // ...cannot all be held.
  assert(btnList.allIdle() == false); // ...cannot all be idle.

  if(btn == &btnA) {
    assert(btnList.anyPressed() == btnB.isPressed());
    assert(btnList.anyHeld() == btnB.isHeld());
    assert(btnList.anyIdle() == btnB.isIdle());
  } else {
    assert(btnList.anyPressed() == btnA.isPressed());
    assert(btnList.anyHeld() == btnA.isHeld());
    assert(btnList.anyIdle() == btnA.isIdle());
  }
}

/**
 * Check ButtonList when button just held.
 */
void checkButtonListJustHeld(Button *btn) {

}

/**
 * Check ButtonList when button just idle.
 */
void checkButtonListJustIdle(Button *btn) {

}

/**
 * Check ButtonList when button just clicked.
 */
void checkButtonListJustClicked(Button *btn) {

}

/**
 * Check ButtonList when button just double-clicked.
 */
void checkButtonListJustDoubleClicked(Button *btn) {

}

/**
 * Check integrity of ButtonList invariants (always hold true).
 */
void checkButtonListIntegrity() {
  // ButtonList::all*() accessors...
  assert(btnList.allPressed() == (btnA.isPressed() && btnB.isPressed()));
  assert(btnList.allHeld() == (btnA.isHeld() && btnB.isHeld()));
  assert(btnList.allIdle() == (btnA.isIdle() && btnB.isIdle()));
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btnList.allClicked() == (btnA.isClicked() && btnB.isClicked()));
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btnList.allDoubleClicked() == (btnA.isDoubleClicked() && btnB.isDoubleClicked()));
# endif

  // ButtonList::any*() accessors...
  assert(btnList.anyPressed() == (btnA.isPressed() || btnB.isPressed()));
  assert(btnList.anyHeld() == (btnA.isHeld() || btnB.isHeld()));
  assert(btnList.anyIdle() == (btnA.isIdle() || btnB.isIdle()));
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btnList.anyClicked() == (btnA.isClicked() || btnB.isClicked()));
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btnList.anyDoubleClicked() == (btnA.isDoubleClicked() || btnB.isDoubleClicked()));
# endif
}
