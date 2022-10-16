/**
 * @file
 * Implementation of button types.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "btntypes.h"

uint8_t jsware::BaseButtonType::debounceTime_ = 50;

void jsware::BaseButtonType::buttonDebounce(uint8_t debounceTime) {
  debounceTime_ = debounceTime;
}

jsware::BaseButtonType::BaseButtonType(uint8_t pin)
:pin_(pin)
,pressed_(false)
,debounce_(0) {
  // NOP
}

void jsware::PulldownButtonType::begin() {
  pinMode(pin_, INPUT);
}

bool jsware::PulldownButtonType::isPressed() {
  bool state = (digitalRead(pin_) == HIGH);

  if(state != pressed_) {
    if(debounce_ == 0) { // Start debounce timer.
      debounce_ = millis();
    } else if(millis() - debounce_ > debounceTime_) {
      pressed_ = state;
      debounce_ = 0;
    }
  }

  return pressed_;
}

void jsware::PullupButtonType::begin() {
  pinMode(pin_, INPUT_PULLUP);
}

bool jsware::PullupButtonType::isPressed() {
  bool state = (digitalRead(pin_) == LOW);

  if(state != pressed_) {
    if(debounce_ == 0) { // Start debounce timer.
      debounce_ = millis();
    } else if(millis() - debounce_ > debounceTime_) {
      pressed_ = state;
      debounce_ = 0;
    }
  }

  return pressed_;
}
