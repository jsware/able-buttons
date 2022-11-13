/**
 * @file Circuits.h Definition of Pulldown and pull-up ressitor circuits.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include <Arduino.h>

namespace able {
  /**
   * Resistor circuit base class. All resistor circuits inherit directly/
   * indirectly from this base class. This class cannot be instantiated
   * directly but it's sub-classes are used by the compile for compile-time
   * template specialisation.
   */
  class Circuit {
    private:
      //
      // Creators, copying and assignment (not supported)...
      //
      Circuit() = delete; ///< Creating resistor circuits is not supported.
      Circuit(const Circuit &) = delete; ///< Copying resistor circuits is not supported.
      Circuit &operator=(const Circuit &) = delete; ///< Assigning resistor circuits is not supported.
  };

  /**
   * Declaration of a pulldown resistor circuit connected to the pin. Pulldown
   * resistors "pull" the pin signal LOW when the button is *not* pressed. When
   * a button is pressed, the signal changes to HIGH as the button is connected
   * to a +ve voltage supply, allowing the current to flow to the pin.
   */
  class PulldownResistorCircuit: private Circuit {
    public:
      //
      // Constants...
      //
      enum {
        PIN_MODE = INPUT,
        BUTTON_PRESSED = HIGH,
        BUTTON_RELEASED = LOW
      };

    private:
      //
      // Creators, copying and assignment (not supported)...
      //
      PulldownResistorCircuit() = delete; ///< Creating resistor circuits is not supported.
      PulldownResistorCircuit(const PulldownResistorCircuit &) = delete; ///< Copying resistor circuits is not supported.
      PulldownResistorCircuit &operator=(const PulldownResistorCircuit &) = delete; ///< Assigning resistor circuits is not supported.
  };

  /**
   * Declaration of a pull-up resistor circuit connected to the pin. Pull-up
   * resistors "pull" the pin signal HIGH when the button is *not* pressed. When
   * a button is pressed, the signal changes to LOW as the button is connected
   * to ground. Using internal pull-up resistors in Arduino microcontrollers
   * allows a button to be connected to ground without any additional resistors.
   * This makes them easy to connect up and use.
   */
  class PullupResistorCircuit: private Circuit {
    public:
      //
      // Constants...
      //
      enum {
        PIN_MODE = INPUT_PULLUP,
        BUTTON_PRESSED = LOW,
        BUTTON_RELEASED = HIGH
      };

    private:
      //
      // Creators, copying and assignment (not supported)...
      //
      PullupResistorCircuit() = delete; ///< Creating resistor objects is not supported.
      PullupResistorCircuit(const PullupResistorCircuit &) = delete; ///< Copying resistor objects is not supported.
      PullupResistorCircuit &operator=(const PullupResistorCircuit &) = delete; ///< Assignment is not supported.
  };
}
