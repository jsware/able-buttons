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
   * Able Buttons. This is the simplest button type. It supports pulldown and
   * pull-up resistor circuits specified using the Circuit.
   * 
   * @param Circuit Either a PullupResistorCircuit or PulldownResistorCircuit
   *                class matching the resistor circuit used with the button.
   * @param PinType The Pin class, or a subclass (DebouncedPin or ClickerPin)
   *                providing additional debounced readings and clicked states.
   */
  template <typename Circuit, typename PinType>
  class Button: public PinType {
    friend void ::loop();

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
      :PinType(pin, Circuit::BUTTON_RELEASED) {}

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
        readPin();
      }

      /**
       * Reset the cliked state of the button, returning what is was. This
       * allows the click state to be effectively read once so that a clicked
       * state only triggers something once, when checked. For example toggling
       * something on/off when the button is clicked. For buttons that don't
       * support clicking, the compile will fail with undefined reference to the
       * resetClicked() method.
       * 
       * @return True if the button was clicked, else false.
       */
      bool resetClicked();

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
       * Determine if the button is clicked. Clicks are registered as a press
       * then release. If the ClickerPin is used, the button returns the click
       * state, otherwise the compile will fail with undefined reference to the
       * isClicked() method.
       * 
       * See the Button<PulldownResistorCircuit, ClickerPin>::isClicked() and
       * Button<PullupResistorCircuit, ClickerPin>::isClicked() specialisations.
       * 
       * @return True if clicked else false.
       */
      bool isClicked() const;
  };

  //
  // Accessor Specialisations...
  //

  /**
   * Specialisation of Button::isClicked() for clickable pins using pulldown
   * resistor circuits.
   * 
   * @return True if clicked (pressed then released), else false.
   */
  template <>
  inline bool Button<PulldownResistorCircuit, ClickerPin>::isClicked() const {
    return currState_ == PulldownResistorCircuit::BUTTON_RELEASED && prevState_ == PulldownResistorCircuit::BUTTON_PRESSED;
  }

  /**
   * Specialisation of Button::isClicked() for clickable pins using pull-up
   * resistor circuits.
   * 
   * @return True if clicked (pressed then released), else false.
   */
  template <>
  inline bool Button<PullupResistorCircuit, ClickerPin>::isClicked() const {    
    return currState_ == PullupResistorCircuit::BUTTON_RELEASED && prevState_ == PullupResistorCircuit::BUTTON_PRESSED;
  }

  //
  // Manipulator Specialisations...
  //

  /**
   * Specialisation of Button::resetClicked() for clickable pins using pulldown
   * resistor circuits.
   * 
   * @return True if resetting a clicked state, else false.
   */
  template <>
  inline bool Button<PulldownResistorCircuit, ClickerPin>::resetClicked() {
    bool rc = isClicked();
    prevState_ = currState_;
    return rc;
  }

  /**
   * Specialisation of Button::resetClicked() for clickable pins using pull-up
   * resistor circuits.
   * 
   * @return True if resetting a clicked state, else false.
   */
  template <>
  inline bool Button<PullupResistorCircuit, ClickerPin>::resetClicked() {
    bool rc = isClicked();
    prevState_ = currState_;
    return rc;
  }
}
