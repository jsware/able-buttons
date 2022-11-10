/**
 * @file callback.h
 * Definitions for handling call-back functions. When a button is pressed,
 * released, clicked etc, a call-back function can be executed.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "button.h"

namespace able {
  /**
   * Return the next auto-assigned button identifier.
   * 
   * @return The next auto-assigned button identifier. Each call increases the
   *         auto-assigned identifier.
   */
  uint8_t autoId();

  /**
   * Callback button template to call a function if the button is pressed.
   * 
   * @param Base The base button class for Callback. Defaults to the Button
   *             template class.
   */
  template <typename Base>
  class CallbackButton: public Base {
    public:
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
                     uint8_t id = autoId())
      :Base(pin), onPressed_(onPressed), onReleased_(onReleased), id_(id) {}

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle();
      
      /**
       * Return the id of the button.
       * 
       * @return The id of the button (auto-assigned or set when created).
       */
      inline uint8_t id() const {
        return id_;
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
    
    protected:
      void (*onPressed_)(uint8_t); ///< Callback function for button press.
      void (*onReleased_)(uint8_t); ///< Callback function for button release.
      uint8_t id_; ///< Identifier for the button passed to callback functions.
  };
}
