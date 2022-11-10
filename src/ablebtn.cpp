/**
 * @file AbleButtons.cpp Implementation of
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "ablebtn.h"

uint8_t AbleButton::debounceTime_ = 50;
 uint8_t AbleButton::autoId_ = 0; ///< Auto-assigned button idedtifier.

bool AbleButton::resetClicked() {
  bool rc = isClicked();
  prevState_ = currState_;
  return rc;
}

void AbleButton::handle() {
  bool currReading = digitalRead(pin_);

  // Reverse reading for pull-up resistors as the pressed state is LOW (0).
  if(mode_ == INPUT_PULLUP) {
    currReading = !currReading;
  }

  // New reading, so start the debounce timer.
  if (currReading != prevReading_) {
    debounceStart_ = millis();
  } else if ((millis() - debounceStart_) >= debounceTime_) {
    if(currReading != currState_) { // Use reading if we have the same reading for >= DELAY ms.
      prevState_ = currState_; // Save previous steady state.
      currState_ = currReading; // Save current reading as current steady state.

      if(currState_ && onPressed_) {
        onPressed_(id_);
      } else if (!currState_ && onReleased_) {
        onReleased_(id_);
      }
    }
  }

  prevReading_ = currReading;
}
