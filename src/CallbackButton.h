/**
 * @file CallbackButton.h Definitions for handling callback functions. When a
 * button is pressed or released, a callback function can called.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "Button.h"

namespace able {
  /**
   * Callback button template to call a function if the button is pressed.
   * 
   * @param Button The base button class for Callback. Defaults to the Button
   *               template class.
   */
  template <typename Button>
  class CallbackButton: public Button {
    public:
      //
      // Creators...
      //

      /**
       * Create a callback button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       * @param onPressed The function to call when the button is pressed.
       * @param onReleased The function to call when the button is released.
       * @param id Callback identifier for the button (default auto-assigned).
       */ 
      inline CallbackButton(uint8_t pin,
                     void(*onPressed)(uint8_t) = 0,
                     void(*onReleased)(uint8_t) = 0,
                     uint8_t id = nextId())
      :Button(pin), onPressed_(onPressed), onReleased_(onReleased), id_(id) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      CallbackButton(const CallbackButton &cpy) = delete; ///< Copying is not supported.
      CallbackButton &operator=(const CallbackButton &) = delete; ///< Assigning is not supported.

    public:
      //
      // Modifiers...
      //

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        uint8_t currState = this->currState_;
        Button::handle();
        if(currState != this->currState_) {
          bool pressed = this->isPressed();
          if(pressed && onPressed_) {
            onPressed_(id_);
          } else if(!pressed && onReleased_) {
            onReleased_(id_);
          }
        }
      }
      
      /**
       * Set a (new) on pressed callback function.
       * 
       * @param callbackFn The function to call when the button is pressed. Use
       *                   0 to clear the on-pressed callback.
       */
      inline void setOnPressed(void(*callbackFn)(uint8_t)) {
        onPressed_ = callbackFn;
      }

      /**
       * Set a (new) on released callback function.
       * 
       * @param callbackFn The function to call when the button is released
       *                   (completing a "click"). Use 0 to clear the
       *                   on-released callback.
       */
      inline void setOnClicked(void(*callbackFn)(uint8_t)) {
        onReleased_ = callbackFn;
      }

    public:
      //
      // Accessors...
      //

      /**
       * Return the id of the button.
       * 
       * @return The id of the button (auto-assigned or set when created).
       */
      inline uint8_t id() const {
        return id_;
      }
    
    protected:
      //
      // Data...
      //
      void (*onPressed_)(uint8_t); ///< Callback function for button press.
      void (*onReleased_)(uint8_t); ///< Callback function for button release.
      uint8_t id_; ///< Identifier for the button passed to callback functions.
  };
}
