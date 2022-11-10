/**
 * @file callback.cpp
 * Callback implementation.
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <Arduino.h>
#include "callback.h"

/**
 * Nasty macro hack to avoid different compile units making their own function.
 * Since the callback handle function is the same regardless of Circuit and Pin
 * configurations, defining template specialisations all the combinations stops
 * it's use in each source code file creating their own per-compile-unit copy.
 * 
 * @param Button The name of the button class to use.
 * @param Circuit The name of the circuit template parameter to use.
 * @param Pin The name of the pin template parameter to use.
 */
#define CallbackButton__handle(Button, Circuit, Pin) template <> \
void CallbackButton<Button<Circuit, Pin>>::handle() { \
  uint8_t currState = this->currState_; \
  Button::handle(); \
  if(currState != this->currState_) { \
    bool pressed = this->isPressed(); \
    if(pressed && onPressed_) { \
      onPressed_(id_); \
    } else if(!pressed && onReleased_) { \
      onReleased_(id_); \
    } \
  } \
}

namespace able {
  static uint8_t autoId_ = 0; ///< Auto-assigned button idedtifier.

  /**
   * Return the next auto-assigned button Id.
   * 
   * @returns The next button id.
   */
  uint8_t autoId() {
    return ++autoId_;
  }

  CallbackButton__handle(Button, PulldownResistorCircuit, DebouncedPin)
  CallbackButton__handle(Button, PulldownResistorCircuit, ClickerPin)
  CallbackButton__handle(Button, PullupResistorCircuit, DebouncedPin)
  CallbackButton__handle(Button, PullupResistorCircuit, ClickerPin)
}
