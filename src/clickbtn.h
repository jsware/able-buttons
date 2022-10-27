/**
 * @file
 * Clickable button handling single click buttons.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_CLICKBTN_H
#define INCLUDED_CLICKBTN_H
#include "basicbtn.h"
#include "btnstate.h"
#include "callback.h"

namespace jsware {
  /**
   * Clickable button template for clickable buttons.
   * 
   * @param ButtonType Either a PullupButtonType or PulldownButtonType
   *                   matching the resistor configuration of the button. Will
   *                   default to PullupButtonType as the simplest button
   *                   connection.
   * @param BaseButton The underlying button to capture clicks from. Defaults to
   *                   a basic button.
   */
  template <typename ButtonType = class PullupButtonType, typename BaseButton = TBasicButton<ButtonType> >
  class TClickableButton {
    public:
      // ClickableButton must be connected via a pin.
      TClickableButton() = delete;

      /**
       * Create a clickable button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       * @param onClicked The function to call when the button is clicked.
       * @param id Callback identifier for the button (default auto-assigned).
       */ 
      TClickableButton(uint8_t pin,
                       void(*onClicked)(uint8_t) = 0,
                       uint8_t id = autoId())
      :button_(pin), id_(id), state_(ButtonState::NONE), onClicked_(onClicked) {}

      /**
       * Initialise the button. Called from setup() of an Arduino program.
       */
      void begin() {
        button_.begin();
      }

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        button_.handle();
        if(!(state_ == ButtonState::PRESSED) && button_.isPressed()) {
          state_ = ButtonState::PRESSED;
        } else if(state_ == ButtonState::PRESSED && !button_.isPressed()) {
          state_ = ButtonState::CLICKED;
          if(onClicked_) {
            onClicked_(id_);
            state_ = ButtonState::NONE;
          }
        }
      }

      /**
       * Set a (new) on clicked callback function.
       * 
       * @param callbackFn The function to call when the button is clicked. Use
       *                   0 to clear the on-clicked callback.
       */
      void onClicked(void(*callbackFn)(uint8_t)) {
        onClicked_ = callbackFn;
      }

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed() {
        return button_.isPressed();
      }

      /**
       * Determine if button was clicked and reset the clicked state.
       * 
       * @return True if button was clicked, false if not.
       */
      bool wasClicked() {
        bool rc = (state_ == ButtonState::CLICKED);
        state_ = ButtonState::NONE;
        return rc;
      }

    private:
      BaseButton button_; ///< The underlying button.
      uint8_t id_; ///< Identifier for the button passed to callback functions.
      uint8_t state_; ///< Indicates the state of the button.
      void (*onClicked_)(uint8_t); ///< Callback function for button click.
  };
}

using ClickableButton = jsware::TClickableButton<jsware::PullupButtonType>; ///< Shorthand for a callback button using a pull-up resistor (most common type).
using ClickablePullupButton = jsware::TClickableButton<jsware::PullupButtonType>; ///< Shorthand for a callback button using a pull-up resistor (explicitly stated).
using ClickablePulldownButton = jsware::TClickableButton<jsware::PulldownButtonType>; ///< Shorthand for a callback button using a pull-down resistor.

#endif /* INCLUDED_CALLBTN_H */
