/**
 * @file button.h
 * Definition of an Able Button.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include <Arduino.h>

/**
 * Able Button class. It supports pulldown and pull-up resistor circuits.
 */
class AbleButton {
  public:
    //
    // Public Static Members...
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

    /**
     * Return the pin debounce time.
     * 
     * @returns The number of milliseconds of debounce time. 
     */
    inline uint8_t debounceTime() const {
      return debounceTime_;
    }

  public:
    //
    // Public Creators...
    //

    /**
     * Create a button on the specified pin.
     * 
     * @param pin The pin connected to the button.
     * @param mode Identifies whether the pin is using a pull-up resistor circuit
     *             (INPUT_PULLUP) or pulldown resistor circuit (INPUT)
     */ 
    inline AbleButton(uint8_t pin,
                      uint8_t mode,
                      void(*onPressed)(uint8_t) = 0,
                      void(*onReleased)(uint8_t) = 0,
                      uint8_t id = ++autoId_)
      :pin_(pin), mode_(mode), onPressed_(onPressed), onReleased_(onReleased), id_(id) {}

  public:
    //
    // Processors...
    //

    /**
     * Initialise the button. Called from setup() of an Arduino program.
     */
    inline void begin() {
      pinMode(pin_, mode_);
    }

    /**
     * Handle the button. Called from loop() of an Arduino program.
     */
    void handle();

  public:
    //
    // Accessors...
    //

    /**
     * Determine if the button is currently pressed.
     * 
     * @return True if pressed, else false.
     */
    inline bool isPressed() const {
      return currState_;
    }

    /**
     * Determine if the button is clicked. Clicks are registered as a press
     * then release.
     * 
     * @return True if clicked else false.
     */
    bool isClicked() const {
      return !currState_ && prevState_; // Not pressed, but was pressed.
    }

    /**
     * Reset the cliked state of the button, returning what is was. This
     * allows the click state to be effectively read once so that a clicked
     * state only triggers something once, when checked. For example toggling
     * something on/off when the button is clicked.
     * 
     * @return True if the button was clicked, else false.
     */
    bool resetClicked();

    /**
     * Return the id of the button.
     * 
     * @return The id of the button (auto-assigned or set when created).
     */
    inline uint8_t id() const {
      return id_;
    }
    
  private:
    //
    // Unsupported operations...
    //
    AbleButton(const AbleButton &cpy) = delete; ///< Copying buttons is not supported.
    AbleButton &operator=(const AbleButton &) = delete; ///< Assigning buttons is not supported.

  public:
    //
    // Private data...
    //
    static uint8_t debounceTime_; ///< Time required to debounce all input pins.
    static uint8_t autoId_; ///< Auto-assigned button id counter.

    uint8_t pin_; ///< The Arduino pin connected to the button.
    uint8_t mode_; ///< Mode for the button.
    bool currState_; ///< The current steady state of the pin.
    bool prevState_; ///< The previous steady state of the pin.
    bool prevReading_; ///< The previous reading from the pin for debouncing.
    unsigned long debounceStart_; ///< Debounce start timer to handle button transition.
    void (*onPressed_)(uint8_t); ///< Callback function for button press.
    void (*onReleased_)(uint8_t); ///< Callback function for button release.
    uint8_t id_; ///< Identifier for the button passed to callback functions.    
};
