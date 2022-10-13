/**
 * @file
 * Definitions of different button types. Supports pull-up and pull-down
 * resistor configurations. Used as a template parameter to the BasicButton
 * class so different pull-up or pull-down resistor configurations return true
 * or false for isPressed().
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_BTNTYPES_H
#define INCLUDED_BTNTYPES_H
#include <Arduino.h>

namespace jsware {
  /**
   * Button connected via a pull-down resistor. Unclosed the signal is low,
   * connected the signal is high.
   */
  class PulldownButtonType {
    public:
      /**
       * Create a pull-down resistor button type on the specified pin.
       * 
       * @param pin The pin to monitor for button presses.
       */
      PulldownButtonType(uint8_t pin)
      :pin_(pin) {}

      /**
       * Initialise the button. Called by TBasicButton.begin and similar.
       */
      void begin() {
        pinMode(pin_, INPUT);
      }

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed() const { return digitalRead(pin_) == HIGH; }

    private:
      uint8_t pin_; ///< The pin connected to the button.
  };

  /**
   * Button connected via a pull-up resistor. Unclosed the signal is high,
   * connected the signal is low.
   */
  class PullupButtonType {
    public:
      /**
       * Create a pull-up resistor button type on the specified pin.
       * 
       * @param pin The pin to monitor for button presses.
       */
      PullupButtonType(uint8_t pin)
      :pin_(pin) {}

      /**
       * Initialise the button. Called by TBasicButton::begin and similar.
       */
      void begin() {
        pinMode(pin_, INPUT_PULLUP);
      }

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed() const { return digitalRead(pin_) == LOW; }

    private:
      uint8_t pin_; ///< @copydoc jsware::PulldownButtonType::pin_
  };
}

#endif /* INCLUDED_BTNTYPES_H */
