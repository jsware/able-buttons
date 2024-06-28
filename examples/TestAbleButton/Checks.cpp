/**
 * @file Checks.cpp Definition of check state of a button functions.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "Checks.h"
#include "Utils.h"

struct ButtonState btnState[NUM_BUTTONS]; ///< Previous state for each button.


/**
 * Check the state of an individual button just setup.
 * 
 * @param btn The button to check. 
 */
void checkButtonSetup(Button *btn) {
  // Given the button, when first setup, then it...
  assert(btn->isPressed() == false); // ...is not pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...is not held.
    assert(btn->isIdle() == false); // ...is not idle.
#endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...is not clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    assert(btn->isDoubleClicked() == false); // ...is not double-clicked.
# endif
}


/**
 * Check state of a pressed button just pressed.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustPressed(Button *btn) {
  // Given a button, when just pressed, then it...
  assert(btn->isPressed() == true); // ...must be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...cannot be held.
    assert(btn->isIdle() == false); // ...cannot be idle.
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...cannot be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    assert(btn->isDoubleClicked() == false); // ...cannot be double-clicked.
# endif
}


/**
 * Check button that has just been released.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustReleased(Button *btn) {
  // Given a button, when just released, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...cannot be held.
    assert(btn->isIdle() == false); // ...cannot be idle.
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...must be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    // assert(btn->isDoubleClicked() == true); // ...*might* be double-clicked.
# endif
}


/**
 * Check button that has just been held.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustHeld(Button *btn) {
  // Given a button, when it is held, then it...
  assert(btn->isPressed() == true); // ...must be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == true); // ...must be held.
    assert(btn->isIdle() == false); // ...cannot be idle.
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...cannot be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    assert(btn->isDoubleClicked() == false); // ...cannot be double-clicked.
# endif
}


/**
 * Check button that has just become or remains idle.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustIdle(Button *btn) {
  // Given a button, when it is idle, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...cannot be held.
    assert(btn->isIdle() == true); // ...will be idle.
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == false); // ...cannot be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    assert(btn->isDoubleClicked() == false); // ...cannot be double-clicked.
# endif
}


/**
 * Check button that has just been clicked.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustClicked(Button *btn) {
  // Given a button, when it just becomes clicked, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...cannot be held.
    assert(btn->isIdle() == false); // ...cannot be idle.
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...must be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    // assert(btn->isDoubleClicked() == false); // ...*might* be double-clicked.
# endif
}


/**
 * Check button that has just been single-clicked.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustSingleClicked(Button *btn) {
  // Given a button, when it just becomes single-clicked, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.
}

/**
 * Check button that has just been double-clicked.
 * 
 * @param btn The button to check. 
 */
void checkButtonJustDoubleClicked(Button *btn) {
  // Given a button, when it just becomes double-clicked, then it...
  assert(btn->isPressed() == false); // ...cannot be pressed.

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    assert(btn->isHeld() == false); // ...cannot be held.
    assert(btn->isIdle() == false); // ...cannot be idle.
#endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btn->isClicked() == true); // ...must be clicked.
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
    assert(btn->isDoubleClicked() == true); // ...will be double-clicked.
# endif
}

/**
 * Check integrity of Button invariants (always hold true).
 * 
 * @param btn The button to check.
 * @param state The tracked state of the button for comparison.
 */
void checkButtonIntegrity(Button *btn, ButtonState &state) {
  // Basic checks...
  if(btn->isPressed()) {
    // Given a pressed button...
    if(!state.isPressed) {
      // ...when it is just pressed, then...
      checkButtonJustPressed(btn);
    } else {
#     if TESTABLE_CLASS >= TESTABLE_BUTTON
        // ...when it is still pressed, then it...
        // assert(btn->isHeld() == false); // ...*might* be held.
        assert(btn->isIdle() == false); // ...cannot be idle.
#     endif

#     if TESTABLE_CLASS >= TESTABLE_CLICKER
        assert(btn->isClicked() == false); // ...cannot be clicked.
#     endif

#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        assert(btn->isSingleClicked() == false); // ...is not exclusively clicked.
        assert(btn->isDoubleClicked() == false); // ...cannot double-clicked.
#     endif
    }
  } else {
    // Given an unpressed button...
    if(state.isPressed) {
      // ...when it is just released, then...
      checkButtonJustReleased(btn);
    } else {
#     if TESTABLE_CLASS >= TESTABLE_BUTTON
        // ...when it is still released, then it...
        assert(btn->isHeld() == false); // ...cannot be held.
        // assert(btn->isIdle() == false); // ...*might* be idle.
#     endif

#     if TESTABLE_CLASS >= TESTABLE_CLICKER
        // assert(btn->isClicked() == false); // ...*might* be clicked.
#     endif

#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        assert(btn->isDoubleClicked() == false); // ...cannot double-clicked.
#     endif
    }
  }


# if TESTABLE_CLASS >= TESTABLE_BUTTON
    if(!state.isHeld && btn->isHeld()) {
      // Given a button that has just become held, then...
      checkButtonJustHeld(btn);
    }

    if(!state.isIdle && btn->isIdle()) {
      // Given a button that has just become idle, then...
      checkButtonJustIdle(btn);
    }
# endif

  // Clickable checks...
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    if(!state.isClicked && btn->isClicked()) {
      // Given a button that has just been clicked, then...
      checkButtonJustClicked(btn);
    }
# endif

  // Double clicker checks...
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    if(!state.isSingleClicked && btn->isSingleClicked()) {
      // given a button that has just been double-clicked, then...
      checkButtonJustSingleClicked(btn);
    }

    if(!state.isDoubleClicked && btn->isDoubleClicked()) {
      // given a button that has just been double-clicked, then...
      checkButtonJustDoubleClicked(btn);
    }
# endif
}


/**
 * Check integrity of ButtonList invariants (always hold true).
 */
void checkButtonListIntegrity() {
  // ButtonList::all*() accessors...
  assert(btnList.allPressed() == (btnA.isPressed() && btnB.isPressed()));

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    // Because isHeld and isIdle use millis() timings, the state can change
    // whilst checking ButtonList::allHeld/Idle and each Button:isHeld/Idle. So
    // checking each twice ensures if the first check is false, it tries once
    // more. Only if both comparisons are false means we have a problem...
    assert(
      (btnList.allHeld() == (btnA.isHeld() && btnB.isHeld())) ||
      (btnList.allHeld() == (btnA.isHeld() && btnB.isHeld()))
    );
    assert(
      (btnList.allIdle() == (btnA.isIdle() && btnB.isIdle())) ||
      (btnList.allIdle() == (btnA.isIdle() && btnB.isIdle()))
    );
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btnList.allClicked() == (btnA.isClicked() && btnB.isClicked()));
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btnList.allSingleClicked() == (btnA.isSingleClicked() && btnB.isSingleClicked()));
    assert(btnList.allDoubleClicked() == (btnA.isDoubleClicked() && btnB.isDoubleClicked()));
# endif

  // ButtonList::any*() accessors...
  assert(btnList.anyPressed() == (btnA.isPressed() || btnB.isPressed()));

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    // Because isHeld and isIdle use millis() timings, the state can change
    // whilst checking ButtonList::anyHeld/Idle and each Button:isHeld/Idle. So
    // checking each twice ensures if the first check is false, it tries once
    // more. Only if both comparisons are false means we have a problem...
    assert(
      (btnList.anyHeld() == (btnA.isHeld() || btnB.isHeld())) ||
      (btnList.anyHeld() == (btnA.isHeld() || btnB.isHeld()))
    );
    assert(
      (btnList.anyIdle() == (btnA.isIdle() || btnB.isIdle())) ||
      (btnList.anyIdle() == (btnA.isIdle() || btnB.isIdle()))
    );
# endif

# if TESTABLE_CLASS >= TESTABLE_CLICKER
    assert(btnList.anyClicked() == (btnA.isClicked() || btnB.isClicked()));
# endif

# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    assert(btnList.anyDoubleClicked() == (btnA.isDoubleClicked() || btnB.isDoubleClicked()));
# endif
}


/**
 * Display button changes to Serial.
 * 
 * @param index Which button in the button list to check.
 */
void displayButtonChanges(int index) {
  Button *btn = btns[index];
  ButtonState &state(btnState[index]);

  // Basic checks...
  if(btn->isPressed()) {
    if(!state.isPressed) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") pressed") << endl;
    }
    state.isPressed = true;
  } else {
    if(state.isPressed) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") released") << endl;
    }
    state.isPressed = false;
  }

# if TESTABLE_CLASS >= TESTABLE_BUTTON
    if(btn->isHeld()) {
      if(!state.isHeld) {
        Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") held") << endl;
      }
      state.isHeld = true;
    } else {
      if(state.isHeld) {
        Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") un-held") << endl;
      }
      state.isHeld = false;
    }

    if(btn->isIdle()) {
      if(!state.isIdle) {
        Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") idle") << endl;
      }
      state.isIdle = true;
    } else {
      if(state.isIdle) {
        Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") un-idle") << endl;
      }
      state.isIdle = false;
    }
# endif

  // Clickable checks...
# if TESTABLE_CLASS >= TESTABLE_CLICKER
    if(btn->isClicked()) {
      if(!state.isClicked) {
        Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") clicked") << endl;
      }
      state.isClicked = true;
    } else if(state.isClicked) {
      state.isClicked = false;
    }
# endif

  // Double clicker checks...
# if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
    if(!state.isDoubleClicked && btn->isDoubleClicked()) {
      Serial << F("Button btns[") << index << F("] (btn") << (char)('A' + index) << F(") double-clicked") << endl;
      state.isDoubleClicked = true;
    } else {
      state.isDoubleClicked = false;
    }
# endif
}
