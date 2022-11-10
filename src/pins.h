/**
 * @file pins.h
 * 
 * Definition of Pin classes (DebouncedPin, ClickerPin), all providing debounce
 * logic when reading from an Arduino pin. Each sub-class adds features.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include <Arduino.h>

namespace able {
  /**
   * Pin base class. All pins inherit directly/indirectly from this base class.
   * This class cannot be instantiated directly. Instantiation comes through
   * sub-classes.
   */
  class Pin {
    protected:
      Pin() {} ///< Constructing pins is supported through sub-classes.

    private:
      Pin(const Pin &) = delete; ///< Copying pins is not supported.
      Pin &operator=(const Pin &) = delete; ///< Assigning pins not supported.
  };

  /**
   * Pin debouncing class. Manages making reliable readings from an input pin.
   * The readPin() function manages debouncing the pin readings. You cannot use
   * this class directly. Use one of the Button sub-classes instead.
   */
  class DebouncedPin: protected Pin {
    protected:
      /**
       * Protected constructor used by sub-classes. Use a sub-class of this
       * class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      inline DebouncedPin(uint8_t pin, uint8_t initState)
      :Pin(), pin_(pin), currState_(initState), prevReading_(initState) {}

      /**
       * Debounce the pin readings to get a stable state of the pin. In order to
       * save memory, virtual functions are *not* used (which can consume almost
       * 1K of memory to deal with). Runtime polymorphism is not required, so
       * avoiding virtual functions saves memory.
       */
      void readPin();

    public:
      /**
       * Set the debounce time for input pins. Pins may read noise as buttons
       * are pressed and released. This noise can be registered as multiple
       * button presses in a short time period, confusing your program. The
       * debounce time is the number of milliseconds to wait when a reading
       * changes before using that reading. See https://docs.arduino.cc/built-in-examples/digital/Debounce
       * for details on debounce.
       * 
       * @param debounceTime The number of milliseconds before a button state change is returned (max 255ms).
       */
      inline static void setDebounceTime(uint8_t debounceTime) {
        debounceTime_ = debounceTime;
      };

      /**
       * Return the pin debounce time.
       * 
       * @returns The number of milliseconds of debounce time. 
       */
      inline uint8_t debounceTime() const {
        return debounceTime_;
      }

    private:
      DebouncedPin(const DebouncedPin &) = delete; ///< Copying pins is not supported.
      DebouncedPin &operator=(const DebouncedPin &) = delete; ///< Assigning pins not supported.

    protected:
      static uint8_t debounceTime_; ///< Time required to debounce all input pins.

      uint8_t pin_; ///< The Arduino pin connected to the button.
      uint8_t currState_; ///< The debounced reading of the pin.
      uint8_t prevReading_; ///< The previous pin reading, to monitor state transitions.
      unsigned long debounceStart_; ///< Debounce start timer to handle button transition.
  };

  /**
   * Pin debouncing class that remembers the previous debounced state. This
   * allows clicks (a combination of press then release) to be identified.
   * This class extends the basic DebouncedPin class to add the previous state.
   */
  class ClickerPin: protected DebouncedPin {
    protected:
      /**
       * Protected constructor used by sub-classes. Use a sub-class of this
       * class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      inline ClickerPin(uint8_t pin, uint8_t initState)
      :DebouncedPin(pin, initState), prevState_(initState) {}

      /**
       * Debounce the pin readings to get a stable state of the pin. When the
       * state changes, remember the previous state so clicks (press then
       * release can be identified). Calls DebouncedPin::readPin() and monitors
       * for a change in debounced state, remembering the previous state.
       */
      void readPin();
      
    private:
      ClickerPin(const ClickerPin &cpy) = delete; ///< Copying pins is not supported.
      ClickerPin &operator=(const DebouncedPin &) = delete; ///< Assigning pins is not supported.

    protected:
      uint8_t prevState_; ///< Previous debounced reading of the pin.
  };
}
