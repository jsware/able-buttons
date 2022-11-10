/**
 * @file button.cpp Button<Circuit, Pin> template specialisations.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "button.h"

namespace able {
  /**
   * Specialisation of Button::resetClicked() for clickable pins using pulldown
   * resistor circuits.
   * 
   * @return True if resetting a clicked state, else false.
   */
  template <>
  bool Button<PulldownResistorCircuit, ClickerPin>::resetClicked() {
    bool rc = isClicked();
    prevState_ = currState_;
    return rc;
  }

  /**
   * Specialisation of Button::resetClicked() for clickable pins using pull-up
   * resistor circuits.
   * 
   * @return True if resetting a clicked state, else false.
   */
  template <>
  bool Button<PullupResistorCircuit, ClickerPin>::resetClicked() {
    bool rc = isClicked();
    prevState_ = currState_;
    return rc;
  }
}