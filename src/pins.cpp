/**
 * @file pins.cpp
 * Implementation of the Pin classes.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "pins.h"

uint8_t able::DebouncedPin::debounceTime_ = 50;

void able::DebouncedPin::readPin() {
  byte currReading = digitalRead(pin_);

  // New reading, so start the debounce timer.
  if (currReading != prevReading_) {
    debounceStart_ = millis();
  } else if ((millis() - debounceStart_) >= debounceTime_) {
    // Use reading if we have the same reading for >= DELAY ms.
    currState_ = currReading;
  }

  prevReading_ = currReading;
}

void able::ClickerPin::readPin() {
  uint8_t currState = currState_; // Remember current state.

  DebouncedPin::readPin();

  // Save previous state if it changed.
  if(currState != currState_) {
    prevState_ = currState;
  }
}
