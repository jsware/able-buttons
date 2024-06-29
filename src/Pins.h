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
   * Pin base class reading direct from the pin (without debouncing). Other pins
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
       * Protected constructor used by sub-classes. Use a Button sub-class
       * instead of this class directly.
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
      //
      // Modifiers...
      //

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
      // Accessors...
      //

      /**
       * Return the number of clicks.
       * 
       * @param pressed The pressed state of a button.
       * @param released The released state of a button.
       * 
       * @returns Always no clicks (0) as clicks not supported by default.
       */
      inline int clicks(uint8_t /* pressed */, uint8_t /* released */) {
        return 0;
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
   * Debouned Pin class. Manages making reliable readings from an input pin.
   * The readPin() method manages debouncing the pin readings. You cannot use
   * this class directly. Use one of the Button sub-classes instead.
   */
  class DebouncedPin: public Pin {
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
       * @param debounceTime The number of milliseconds before a button state
       *                     change is returned (default 50ms, max 255ms).
       */
      inline static void setDebounceTime(uint8_t debounceTime) {
        debounceTime_ = debounceTime;
      };

      /**
       * Set the held time for input pins. If a button is pressed for longer
       * than this time, it will be held.
       * 
       * @param heldTime The number of milliseconds for a held state (default 1s).
       */
      inline static void setHeldTime(uint16_t heldTime) {
        heldTime_ = heldTime;
      }

      /**
       * Set the idle time for input pins. If a button is unpressed for longer
       * than this time, it will be idle.
       * 
       * @param idleTime The number of milliseconds for an idle state (default 60s).
       */
      inline static void setIdleTime(uint32_t idleTime) {
        idleTime_ = idleTime;
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
          millisStart_ = millis();
        } else if ((millis() - millisStart_) >= debounceTime_) {
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
      static inline uint8_t debounceTime() {
        return debounceTime_;
      }

      /**
       * Return the pin held time.
       * 
       * @returns The number of milliseconds after which a pin is held.
       */
      static inline uint16_t heldTime() {
        return heldTime_;
      }

      /**
       * Return the pin idle time.
       * 
       * @returns The number of milliseconds after which a pin is idle.
       */
      static inline uint32_t idleTime() {
        return idleTime_;
      }

    protected:
      //
      // Data...
      //
      static uint8_t debounceTime_; ///< Time required to debounce all input pins.
      static uint16_t heldTime_; ///< Time required for button to be held.
      static uint32_t idleTime_; ///< Time required for button to be idle.

      uint8_t prevReading_; ///< The previous pin reading, to monitor state transitions.
      unsigned long millisStart_; ///< Debounce start timer to handle button transition.
  };

  /**
   * Debounced pin class that remembers the previous debounced state. This
   * allows clicks (a combination of press then release) to be identified.
   * This class extends the basic DebouncedPin class to add the previous state.
   */
  class ClickerPin: public DebouncedPin {
    protected:
      //
      // Creators...
      //

      /**
       * Protected constructor used by sub-classes. Use a Button sub-class of
       * this class instead of this class directly.
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
      ClickerPin &operator=(const ClickerPin &) = delete; ///< Assigning pins is not supported.

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
      // Accessors...
      //

      /**
       * Return the number of clicks.
       * 
       * @param pressed The pressed state of a button.
       * @param released The released state of a button.
       * 
       * @returns Always single clicks (1) as double-clicks not supported.
       */
      inline int clicks(uint8_t pressed, uint8_t released) {
        return this->currState_ == released && this->prevState_ == pressed;
      }

      protected:
      //
      // Data...
      //
      uint8_t prevState_; ///< Previous debounced reading of the pin.
  };

  /**
   * Pin class that counts state changes within a time-period. This enables it
   * to identify double-clicks.
   */
  class DoubleClickerPin: public ClickerPin {
    public:
      //
      // Static Members...
      //

      /**
       * Set the click time for input pins. If a button is clicked again
       * within this millisecond value, it will be counted, else the count
       * resets. Allows tracking of double-clicks within the specified time.
       * 
       * @param clickTime The number of milliseconds between clicks.
       */
      inline static void setClickTime(uint16_t clickTime) {
        clickTime_ = clickTime / 2; // Halve clickTime as we count presses and releases.
      }

    protected:
      //
      // Creators...
      //

      /**
       * Protected constructor used by sub-classes. Use a Button sub-class of
       * this class instead of this class directly.
       * 
       * @param pin The pin to read from.
       * @param initState The initial (un-pushed) state of the button.
       */
      DoubleClickerPin(uint8_t pin, uint8_t initState)
      :ClickerPin(pin, initState) {}

    private:
      //
      // Copying and assignment (not supported)...
      //
      DoubleClickerPin(const DoubleClickerPin &cpy) = delete; ///< Copying pins is not supported.
      DoubleClickerPin &operator=(const DoubleClickerPin &) = delete; ///< Assigning pins is not supported.

    public:
      //
      // Accessors...
      //

      /**
       * Return the double-click time.
       * 
       * @returns The number of milliseconds of debounce time. 
       */
      static inline uint16_t clickTime() {
        return clickTime_ * 2; // Double the clickTime_ to match halving in setClickTime.
      }

      /**
       * Return the number of clicks.
       * 
       * @param pressed The pressed state of a button.
       * @param released The released state of a button.
       * 
       * @returns no click (0), single click (1) or double-click (2).
       */
      inline int clicks(uint8_t /* pressed */, uint8_t /* released */) const {
        if(this->stateCount_ >= 4) {
          return 2;
        } else {
          return this->stateCount_ == 2 && ((millis() - this->millisStart_) >= this->clickTime_);
        }
      }

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

        // NB: Calls DebouncedPin version to avoid remembering current state
        // twice.
        DebouncedPin::readPin();

        // Save previous state & millis if it changed.
        if(currState != currState_) {
          prevState_ = currState;
          if(millisStart_ - prevMillis_ < clickTime_) {
            ++stateCount_;
          } else {
            stateCount_ = 1;
          }
          prevMillis_ = millisStart_;
        }
      }
      
    protected:
      //
      // Data...
      //
      static uint16_t clickTime_; ///< Time required for button to be double-clicked.

      uint8_t stateCount_; ///< Count changes in state within double-click time.
      unsigned long prevMillis_; ///< Previous millisecond count from last state change.
  };
}
