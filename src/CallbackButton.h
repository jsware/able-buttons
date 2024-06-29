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
        IDLE_EVENT, ///< The button has been idle (untouched) for a while.
        SINGLE_CLICKED_EVENT, ///< The button has been clicked (pressed+released).
        DOUBLE_CLICKED_EVENT  ///< The button has been double-clicked.
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
        this->doCallback(BEGIN_EVENT);
      }

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        uint8_t currState = this->currState_;
        Button::handle();
        if(currState != this->currState_) {
          if(this->isPressed()) {
            this->doCallback(PRESSED_EVENT);
          } else {
            this->doCallback(RELEASED_EVENT);
          }
        } else if(lastEvent_ != HELD_EVENT && this->isHeld()) {
            this->doCallback(HELD_EVENT);
        } else if(lastEvent_ != IDLE_EVENT && this->isIdle()) {
            this->doCallback(IDLE_EVENT);
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

    protected:
      inline void doCallback(CALLBACK_EVENT event) {
        lastEvent_ = event;
        if(callbackFn_) callbackFn_(event, id_);
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
      CALLBACK_EVENT lastEvent_; ///< Indicates the last event sent.
  };

  /**
   * Callback clicker button template to call a function if the button is pressed.
   * 
   * @param Button The base button class for Callback. Defaults to the Button
   *               template class.
   */
  template <typename Button>
  class CallbackClickerButton: public Button {
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
      inline CallbackClickerButton(uint8_t pin,
                     void(*callbackFn)(enum Button::CALLBACK_EVENT, uint8_t) = 0,
                     uint8_t id = Pin::nextId())
      :Button(pin, callbackFn, id) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      CallbackClickerButton(const CallbackClickerButton &cpy) = delete; ///< Copying is not supported.
      CallbackClickerButton &operator=(const CallbackClickerButton &) = delete; ///< Assigning is not supported.

    public:
      //
      // Modifiers...
      //

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        Button::handle();
        if(this->lastEvent_ == Button::RELEASED_EVENT) {
          switch(Button::clicks(Button::BUTTON_PRESSED, Button::BUTTON_RELEASED)){
            case 1:
              this->doCallback(Button::SINGLE_CLICKED_EVENT);
              break;

            case 2:
              this->doCallback(Button::DOUBLE_CLICKED_EVENT);
              break;

            default: // No clicks.
              break;
          }
        }
      }
  };
}
