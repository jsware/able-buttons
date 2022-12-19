/**
 * @file CheckButton.cpp Check state of a button.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

void checkButtonSetup(Button *btn) {
  // Given the button, when first setup, then...
  assert(btn->isPressed() == false); // ...it is not pressed.
  assert(btn->isHeld() == false); // ...it is not held.
  assert(btn->isIdle() == false); // ...it is not idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...it is not clicked
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isDoubleClicked() == false); // ...it is not double-clicked.
# endif
}

/**
 * Check state of a pressed button...
 */
void checkButtonJustPressed(Button *btn) {
  // Given a button, when just pressed, then...
  assert(btn->isPressed() == true); // ...it must be pressed.
  assert(btn->isHeld() == false); // ...it cannot be held.
  assert(btn->isIdle() == false); // ...it cannot be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...it cannot be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isDoubleClicked() == false); // ...it cannot be double-clicked.
# endif
}

/**
 * Check button that has just been released.
 */
void checkButtonJustReleased(Button *btn) {
  // Given a button, when just released, then...
  assert(btn->isPressed() == false); // ...it cannot be pressed.
  assert(btn->isHeld() == false); // ...it cannot be held.
  assert(btn->isIdle() == false); // ...it cannot be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...it must be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    // assert(btn->isDoubleClicked() == true); // ...it *might* be double-clicked.
# endif
}

/**
 * Check button that has just been held.
 */
void checkButtonJustHeld(Button *btn) {
  // Given a button, when it just becomes held, then...
  assert(btn->isPressed() == true); // ...it must be pressed.
  assert(btn->isHeld() == true); // ...it must be held.
  assert(btn->isIdle() == false); // ...it cannot be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...it cannot be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isDoubleClicked() == false); // ...it cannot be double-clicked.
# endif
}

/**
 * Check button that has just become idle.
 */
void checkButtonJustIdle(Button *btn) {
  // Given a button, when it just becomes idle, then...
  assert(btn->isPressed() == false); // ...it must not be pressed.
  assert(btn->isHeld() == false); // ...it must not be held.
  assert(btn->isIdle() == true); // ...it must be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...it cannot be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isDoubleClicked() == false); // ...it cannot be double-clicked.
# endif
}

/**
 * Check button that has just been clicked.
 */
void checkButtonJustClicked(Button *btn) {
  // Given a button, when it just becomes clicked, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.
  assert(btn->isHeld() == false); // ...cannot be held.
  assert(btn->isIdle() == false); // ...cannot be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...must be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    // assert(btn->isDoubleClicked() == false); // ...*might* be double-clicked.
# endif
}

/**
 * Check button that has just been double-clicked.
 */
void checkButtonJustDoubleClicked(Button *btn) {
  // Given a button, when it just becomes double-clicked, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.
  assert(btn->isHeld() == false); // ...cannot be held.
  assert(btn->isIdle() == false); // ...cannot be idle.
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...must be clicked.
# endif
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    // assert(btn->isDoubleClicked() == true); // ...*might* be double-clicked.
# endif
}

/**
 * Check integrity of Button invariants (always hold true).
 */
void checkButtonIntegrity(Button *btn, ButtonState &state) {
  // Basic checks...
  if(btn->isPressed()) {
    // Given a pressed button...
    if(!state.isPressed) {
      // ...when it is just pressed, then...
      checkButtonJustPressed(btn);
    } else {
      // ...when it is still pressed, then it...
      // assert(btn->isHeld() == false); // ...*might* be held.
      assert(btn->isIdle() == false); // ...cannot be idle.
#     if TESTABLE_CLASS >= TESTABLE_CLICKER
        assert(btn->isClicked() == false); // ...cannot be clicked.
#     endif
#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        assert(btn->isDoubleClicked() == false); // ...cannot double-clicked.
#     endif
    }
  } else {
    // Given an unpressed button...
    if(state.isPressed) {
      // ...when it is just released, then...
      checkButtonJustReleased(btn);
    } else {
      // ...when it is still released, then it...
      assert(btn->isHeld() == false); // ...cannot be held.
      // assert(btn->isIdle() == false); // ...*might* be idle.
#     if TESTABLE_CLASS >= TESTABLE_CLICKER
        assert(btn->isClicked() == false); // ...cannot be clicked.
#     endif
#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        assert(btn->isDoubleClicked() == false); // ...cannot double-clicked.
#     endif
    }
  }

  if(!state.isHeld && btn->isHeld()) {
    checkButtonJustHeld(btn);
  }

  if(!state.isIdle && btn->isIdle()) {
    checkButtonJustIdle(btn);
  }

  // Clickable checks...
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    if(!state.isClicked && btn->isClicked()) {
      checkButtonJustClicked(btn);
    }
# endif

  // Double clicker checks...
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    if(!state.isDoubleClicked && btn->isDoubleClicked()) {
      checkButtonJustDoubleClicked(btn);
    }
# endif
}

void displayButton(Button *btn, ButtonState &state, int index) {
  // Basic checks...
  if(btn->isPressed()) {
    if(!state.isPressed) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") pressed") << endl;
    }
  } else {
    if(state.isPressed) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") released") << endl;
    }
  }

  if(!state.isHeld && btn->isHeld()) {
    Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") held") << endl;
  }

  if(!state.isIdle && btn->isIdle()) {
    Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") idle") << endl;
  }

  // Clickable checks...
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    if(!state.isClicked && btn->isClicked()) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") clicked") << endl;
    }
# endif

  // Double clicker checks...
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    if(!state.isDoubleClicked && btn->isDoubleClicked()) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") double-clicked") << endl;
    }
# endif
}
