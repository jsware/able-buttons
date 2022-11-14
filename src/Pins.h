/**
 * @file Pins.h Definition of the Pin class and subclasses (DebouncedPin,
 * ClickerPin), providing debounce logic when reading from an Arduino pin. Each
 * sub-class adds features for the pin (e.g. remembering clicks).
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include <Arduino.h>

namespace able {
  /**
   * Pin base class reading direct from the pin (without debouncing). All pins
   * inherit directly/indirectly from this base class. This class cannot be
   * instantiated directly. Instantiation comes through Button sub-classes.
   */
  class Pin {
    protected:
      //
      // Static Members...
      //

      /**
       * Return the next auto-assigned button identifier.
       * 
       * @return The next auto-assigned button identifier. Each call increases the
       *         auto-assigned identifier.
       */
      inline static uint8_t nextId() {
        return ++autoId_;
      }

    protected:
      //
      // Creators...
      //

      /**
       * Protected constructor used by sub-classes. Use a sub-class of this
       * class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      inline Pin(uint8_t pin, uint8_t initState)
      :pin_(pin), currState_(initState) {}

    private:
      //
      // Copy and assignment (not supported)...
      //
      Pin(const Pin &) = delete; ///< Copying pins is not supported.
      Pin &operator=(const Pin &) = delete; ///< Assigning pins not supported.

    protected:
      /**
       * Read the pin directly. In order to save memory, virtual functions are
       * *not* used (which can consume almost 1K of memory to deal with).
       * Runtime polymorphism is not required, so avoiding virtual functions
       * saves memory.
       */
      inline void readPin() {
        currState_ = digitalRead(pin_);
      }

    protected:
      //
      // Data...
      //
      static uint8_t autoId_; ///< Auto-assigned button identifier.

      uint8_t pin_; ///< The Arduino pin connected to the button.
      uint8_t currState_; ///< The reading of the pin.
  };

  /**
   * Pin debouncing class. Manages making reliable readings from an input pin.
   * The readPin() function manages debouncing the pin readings. You cannot use
   * this class directly. Use one of the Button sub-classes instead.
   */
  class DebouncedPin: protected Pin {
    public:
      //
      // Static Members...
      //

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

    protected:
      //
      // Creators...
      //

      /**
       * Protected constructor used by sub-classes. Use a sub-class of this
       * class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      DebouncedPin(uint8_t pin, uint8_t initState)
      :Pin(pin, initState), prevReading_(initState) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      DebouncedPin(const DebouncedPin &) = delete; ///< Copying pins is not supported.
      DebouncedPin &operator=(const DebouncedPin &) = delete; ///< Assigning pins not supported.

    protected:
      //
      // Modifiers...
      //

      /**
       * Debounce the pin readings to get a stable state of the pin. In order to
       * save memory, virtual functions are *not* used (which can consume almost
       * 1K of memory to deal with). Runtime polymorphism is not required, so
       * avoiding virtual functions saves memory.
       */
      inline void readPin() {
        byte currReading = digitalRead(pin_);

        // New reading, so start the debounce timer.
        if (currReading != prevReading_) {
          debounceStart_ = millis();
        } else if ((millis() - debounceStart_) >= debounceTime_) {
          // Use reading if we have the same reading for >= DELAY ms.
          currState_ = currReading;
        }

        prevReading_ = currReading;
      }

    public:
      //
      // Accessors...
      //

      /**
       * Return the pin debounce time.
       * 
       * @returns The number of milliseconds of debounce time. 
       */
      inline uint8_t debounceTime() const {
        return debounceTime_;
      }

    protected:
      //
      // Data...
      //
      static uint8_t debounceTime_; ///< Time required to debounce all input pins.

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
      //
      // Creators...
      //

      /**
       * Protected constructor used by sub-classes. Use a sub-class of this
       * class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      ClickerPin(uint8_t pin, uint8_t initState)
      :DebouncedPin(pin, initState), prevState_(initState) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      ClickerPin(const ClickerPin &cpy) = delete; ///< Copying pins is not supported.
      ClickerPin &operator=(const DebouncedPin &) = delete; ///< Assigning pins is not supported.

    protected:
      //
      // Modifiers...
      //

      /**
       * Debounce the pin readings to get a stable state of the pin. When the
       * state changes, remember the previous state so clicks (press then
       * release can be identified). Calls DebouncedPin::readPin() and monitors
       * for a change in debounced state, remembering the previous state.
       */
      inline void readPin() {
        uint8_t currState = currState_; // Remember current state.

        DebouncedPin::readPin();

        // Save previous state if it changed.
        if(currState != currState_) {
          prevState_ = currState;
        }
      }
      
    protected:
      //
      // Data...
      //
      uint8_t prevState_; ///< Previous debounced reading of the pin.
  };
}
