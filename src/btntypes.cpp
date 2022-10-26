/**
 * @file
 * Implementation of button types.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "btntypes.h"

uint8_t jsware::PulldownButtonType::debounceTime_ = 50;
uint8_t jsware::PullupButtonType::debounceTime_ = 50;

jsware::PulldownButtonType::PulldownButtonType(uint8_t pin)
:pin_(pin)
,state_(0)
,last_(0)
,debounce_(0) {
  // NOP
}

void jsware::PulldownButtonType::begin() {
  pinMode(pin_, INPUT);
}

void jsware::PulldownButtonType::handle() {
  byte reading = digitalRead(pin_);

  // New reading, so start the debounce timer.
  if (reading != last_) {
    debounce_ = millis();
  } else if ((millis() - debounce_) >= debounceTime_) {
    // Use reading if we have the same reading for >= debounce time.
    state_ = reading;
  }

  last_ = reading;
}

jsware::PullupButtonType::PullupButtonType(uint8_t pin)
:pin_(pin)
,state_(0)
,last_(0)
,debounce_(0) {
  // NOP
}

void jsware::PullupButtonType::begin() {
  pinMode(pin_, INPUT_PULLUP);
}

void jsware::PullupButtonType::handle() {
  byte reading = digitalRead(pin_);

  // New reading, so start the debounce timer.
  if (reading != last_) {
    debounce_ = millis();
  } else if ((millis() - debounce_) >= debounceTime_) {
    // Use reading if we have the same reading for >= DELAY ms.
    state_ = reading;
  }

  last_ = reading;
}
