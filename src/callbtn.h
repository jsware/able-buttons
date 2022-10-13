/**
 * @file
 * Callback Button to call a function when pressed.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_CALLBTN_H
#define INCLUDED_CALLBTN_H
#include "basicbtn.h"

namespace jsware {
  /**
   * Callback button template to call a function if the button is pressed.
   * 
   * @param ButtonType Either a PullupButtonType or PulldownButtonType
   *                   matching the resistor configuration of the button. Will
   *                   default to PullupButtonType as the simplest button
   *                   connection.
   */
  template <typename ButtonType = class PullupButtonType, typename BaseButton = TBasicButton<ButtonType> >
  class TCallbackButton: public BaseButton {
    public:
      // CallbackButton must be connected via a pin.
      TCallbackButton() = delete;

      /**
       * Create a basic button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       * @param onPressed The function to call when the button is pressed.
       * @param onReleased The function to call when the button is released.
       */ 
      TCallbackButton(uint8_t pin
                     ,void(*onPressed)(BaseButton *btn) = 0
                     ,void(*onReleased)(BaseButton *btn) = 0)
      :TBasicButton<ButtonType>(pin)
      ,pressed_(false)
      ,onPressed_(onPressed)
      ,onReleased_(onReleased) {}

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        if(!pressed_ && BaseButton::isPressed()) {
          pressed_ = true;
          if(onPressed_) {
            onPressed_(this);
          }
        } else if(pressed_ && !BaseButton::isPressed()) {
          pressed_ = false;
          if(onReleased_) {
            onReleased_(this);
          }
        }
      }

    private:
      bool pressed_; ///< Indicates if the button was previously pressed.
      void (*onPressed_)(BaseButton *); ///< Callback function for button press.
      void (*onReleased_)(BaseButton *); ///< Callback function for button release.
  };
}

using CallbackButton = jsware::TCallbackButton<jsware::PullupButtonType>; ///< Shorthand for a callback button using a pull-up resistor (most common type).
using CallbackPullupButton = jsware::TCallbackButton<jsware::PullupButtonType>; ///< Shorthand for a callback button using a pull-up resistor (explicitly stated).
using CallbackPulldownButton = jsware::TCallbackButton<jsware::PulldownButtonType>; ///< Shorthand for a callback button using a pull-down resistor.

#endif /* INCLUDED_CALLBTN_H */
