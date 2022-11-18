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
      /**
       * Button event codes. When a callback function is called, the first
       * argument is an event code below.
       */
      enum CALLBACK_EVENT {
        BEGIN_EVENT, ///< The button's begin() method has completed.
        PRESSED_EVENT, ///< The button has been pressed.
        RELEASED_EVENT, ///< The button has been released.
        HELD_EVENT, ///< The button has been held down for a while.
        IDLE_EVENT ///< The button has been idle (untouched) for a while.
      };

    public:
      //
      // Creators...
      //

      /**
       * Create a callback button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       * @param callbackFn The function to call when the button is pressed.
       * @param id Callback identifier for the button (default auto-assigned).
       */ 
      inline CallbackButton(uint8_t pin,
                     void(*callbackFn)(enum CALLBACK_EVENT, uint8_t) = 0,
                     uint8_t id = Pin::nextId())
      :Button(pin), callbackFn_(callbackFn), id_(id) {}

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
       * Initialise the button. Called from setup() of an Arduino program.
       */
      void begin() {
        Button::begin();
        if(callbackFn_) {
          callbackFn_(BEGIN_EVENT, id_);
        }
      }

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        uint8_t currState = this->currState_;
        Button::handle();
        if(currState != this->currState_) {
          longEvent_ = false;
          if(callbackFn_) {
            if(this->isPressed()) {
              callbackFn_(PRESSED_EVENT, id_);
            } else {
              callbackFn_(RELEASED_EVENT, id_);
            }
          }
        } else if(!longEvent_ && callbackFn_) {
          if(this->isHeld()) {
            longEvent_ = true;
            callbackFn_(HELD_EVENT, id_);
          } else if(this->isIdle()) {
            longEvent_ = true;
            callbackFn_(IDLE_EVENT, id_);
          }
        }
      }
      
      /**
       * Set a (new) callback function.
       * 
       * @param callbackFn The function to call for a button event. Use 0 to
       *                   clear the callback function.
       */
      inline void setCallback(void(*callbackFn)(CALLBACK_EVENT, uint8_t)) {
        callbackFn_ = callbackFn;
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
      void (*callbackFn_)(enum CALLBACK_EVENT, uint8_t); ///< Callback function.
      uint8_t id_; ///< Identifier for the button passed to callback functions.
      bool longEvent_; ///< Indicates the held/idle event has been sent.
  };
}
