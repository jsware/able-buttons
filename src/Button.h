/**
 * @file Button.h Definition of the core Able Button template class.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "Circuits.h"
#include "Pins.h"

namespace able {
  /**
   * Core Button class. It supports pulldown and pull-up resistor circuits
   * specified using the Circuit template parameter and different pin features
   * using the Pin template parameter.
   * 
   * @param Circuit Either a PullupResistorCircuit or PulldownResistorCircuit
   *                class matching the resistor circuit used with the button.
   * @param Pin The Pin class, or a subclass (DebouncedPin or ClickerPin)
   *            providing additional debounced readings and clicked states.
   */
  template <typename Circuit, typename Pin>
  class Button: public Pin {
    public:
      //
      // Constants...
      //
      enum {
        BUTTON_PRESSED = Circuit::BUTTON_PRESSED,
        BUTTON_RELEASED = Circuit::BUTTON_RELEASED
      };

    public:
      //
      // Creators...
      //

      /**
       * Create a button on the specified pin.
       * 
       * @param pin The pin connected to the button.
       */ 
      Button(uint8_t pin)
      :Pin(pin, Circuit::BUTTON_RELEASED) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      Button(const Button &cpy) = delete; ///< Copying is not supported.
      Button &operator=(const Button &) = delete; ///< Assigning buttons is not supported.

    public:
      //
      // Modifiers...
      //

      /**
       * Initialise the button. Called from setup() of an Arduino program.
       */
      void begin() {
        pinMode(this->pin_, Circuit::PIN_MODE);
      }

      /**
       * Handle the button. Called from loop() of an Arduino program.
       */
      void handle() {
        this->readPin();
      }

      /**
       * Reset the clicked state of the button, returning what is was. This
       * allows the click state to be effectively read once so that a clicked
       * state only triggers something once, when checked. For example toggling
       * something on/off when the button is clicked. For buttons that don't
       * support clicking, the compile will fail with errors.
       * 
       * @return True if the button was clicked, else false.
       */
      bool resetClicked() {
        bool rc = this->isClicked();
        this->prevState_ = this->currState_;
        return rc;
      }

      /**
       * Reset the clicked state of the button, returning what is was. This
       * allows the click state to be effectively read once so that a clicked
       * state only triggers something once, when checked. For example toggling
       * something on/off when the button is clicked. For buttons that don't
       * support clicking, the compile will fail with errors.
       * 
       * @return True if the button was clicked, else false.
       */
      bool resetSingleClicked() {
        bool rc = this->isSingleClicked();
        if(rc) this->stateCount_ = 0;
        return rc;
      }

      /**
       * Reset the double-clicked state of the button, returning what is was.
       * This allows the double-click state to be effectively read once so that
       * a double-clicked state only triggers something once, when checked.
       * For example toggling something on/off when the button is double-
       * clicked. For buttons that don't support double-clicking, the compile
       * will fail with errors.
       * 
       * @return True if the button was double-clicked, else false.
       */
      bool resetDoubleClicked() {
        bool rc = this->isDoubleClicked();
        if(rc) this->stateCount_ = 0;
        return rc;
      }

    public:
      //
      // Accessors...
      //

      /**
       * Determine if the button is currently pressed.
       * 
       * @return True if pressed, else false.
       */
      bool isPressed() const {
        return this->currState_ == Circuit::BUTTON_PRESSED;
      }

      /**
       * Determine if the button is currently held down.
       * 
       * @return True if held, else false.
       */
      bool isHeld() const {
        return isPressed() && ((millis() - this->millisStart_) >= this->heldTime_);
      }

      /**
       * Determine if the button is currently idle (unpressed for a "long" time).
       * 
       * @return True if idle, else false.
       */
      bool isIdle() const {
        return !isPressed() && ((millis() - this->millisStart_) >= this->idleTime_);
      }
      
      /**
       * Determine if the button is clicked. Clicks are registered as a press
       * then release. If the ClickerPin (or subclass) is used, the button
       * returns the click state, otherwise the compile will fail with errors.
       * 
       * @return True if clicked else false.
       */
      bool isClicked() const {
        return this->currState_ == Circuit::BUTTON_RELEASED && this->prevState_ == Circuit::BUTTON_PRESSED;
      }

      /**
       * Determine if the button is exclusively single-clicked. Clicks are
       * registered as a press then release. Single-clicks wait until any
       * double-click time has passed to ensure it's exclusively a click and not
       * the first click in a double-click sequence. If the DoubleClickerPin is
       * used, the button returns the single-click state, otherwise the compile
       * will fail with errors.
       * 
       * @return True if exclusively clicked else false.
       */
      bool isSingleClicked() const {
        return this->stateCount_ == 2 && ((millis() - this->millisStart_) >= this->clickTime_);
      }

      /**
       * Determine if the button is double-clicked. Double-clicks are registered
       * as two clicks within the double-click time. If the DoubleClickPin is
       * used, the button returns the double-click state, otherwise the compile
       * will fail with errors.
       * 
       * @return True if double-clicked else false.
       */
      bool isDoubleClicked() const {
        return this->stateCount_ >= 4;
      }
  };
}
