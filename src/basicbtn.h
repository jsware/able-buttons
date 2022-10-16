/**
 * @file
 * Simplest button to check if currently pressed.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_BASICBTN_H
#define INCLUDED_BASICBTN_H
#include "btntypes.h"

namespace jsware {
  /**
   * Simplest button class to check if the button has been pressed.
   * 
   * @param ButtonType Either a PullupButtonType or PulldownButtonType
   *                   matching the resistor configuration of the button. Will
   *                   default to PullupButtonType as the simplest button
   *                   connection.
   */
  template <typename ButtonType = class PullupButtonType>
  class TBasicButton {
    public:
      // BasicButton must be connected via a pin.
      TBasicButton() = delete;

      /**
       * Create a basic button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       */ 
      TBasicButton(uint8_t pin)
      :button_(pin) {};

      /**
       * Initialise the button. Called from setup() of an Arduino program.
       */
      void begin() {
        button_.begin();
      }

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed() {
        return button_.isPressed();
      }

    private:
      ButtonType button_; ///< The PullupButtonType or PulldownButtonType
  };
}

using BasicButton = jsware::TBasicButton<jsware::PullupButtonType>; ///< Shorthand for a basic button using a pull-up resistor (most common type).
using BasicPullupButton = jsware::TBasicButton<jsware::PullupButtonType>; ///< Shorthand for a basic button using a pull-up resistor (explicitly stated).
using BasicPulldownButton = jsware::TBasicButton<jsware::PulldownButtonType>; ///< Shorthand for a basic button using a pull-down resistor.

#endif /* INCLUDED_BASICBTN_H */
