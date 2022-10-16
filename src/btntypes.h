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
   * Base class for buttont types. 
   */
  class BaseButtonType {
    public:
      /**
       * Set the debounce time for buttons. Buttons may generate noise as they
       * are pressed and released. This noise can be registered as multiple
       * button presses in a short time period, confusing a program. The
       * debounce time is the number of milliseconds to wait when a button state
       * changes before returning that change with the isPressed() methods. See
       * https://docs.arduino.cc/built-in-examples/digital/Debounce for details
       * on debounce.
       * 
       * @param debounceTime The number of milliseconds before a button state change is returned (max 255ms).
       */
      static void buttonDebounce(uint8_t debounceTime);

      /**
       * Create a button type on the specified pin.
       * 
       * @param pin The pin to monitor for button presses.
       */
      BaseButtonType(uint8_t pin);

    protected:
      static uint8_t debounceTime_; ///< The time required to debounce a button.

      uint8_t pin_; ///< The pin connected to the button.
      bool pressed_; ///< Indicator whether the button is pressed or not.
      unsigned long debounce_; ///< Debounce timer to handle button transition.
  };

  /**
   * Button connected via a pull-down resistor. Unclosed the signal is low,
   * connected the signal is high.
   */
  class PulldownButtonType : public BaseButtonType {
    public:
      /**
       * Create a pull-down resistor button type on the specified pin.
       * 
       * @param pin The pin to monitor for button presses.
       */
      PulldownButtonType(uint8_t pin): BaseButtonType(pin) {}

      /**
       * Initialise the button. Called by TBasicButton.begin and similar.
       */
      void begin();

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed();
  };

  /**
   * Button connected via a pull-up resistor. Unclosed the signal is high,
   * connected the signal is low.
   */
  class PullupButtonType: public BaseButtonType {
    public:
      /**
       * Create a pull-up resistor button type on the specified pin.
       * 
       * @param pin The pin to monitor for button presses.
       */
      PullupButtonType(uint8_t pin): BaseButtonType(pin) {}

      /**
       * Initialise the button. Called by TBasicButton::begin and similar.
       */
      void begin();

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed();
  };
}

#endif /* INCLUDED_BTNTYPES_H */
