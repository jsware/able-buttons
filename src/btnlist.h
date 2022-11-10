/**
 * @file btnlist.h
 * Definitions of a button list. ButtonList allows an array of buttons to be
 * controlled via a single begin() and handle() calls. Useful for programs that
 * use multiple buttons.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "button.h"

namespace able {
  /**
   * Template for a list of buttons of the same type. Allows a set of buttons
   * to be controlled together. NB: You cannot mix different button types in the
   * same button list. Use separate lists to manage collections of pulldown, 
   * and pull-up resistors, buttons and clickers) s in the same list (use
   * separate lists).
   */
  template <typename Button>
  class ButtonList {
    public:
      /**
       * Create a list of buttons. Makes beginning and handling of a set of
       * buttons easier.
       * 
       * @param buttons The array of buttons to manage together.
       */
      template <size_t n>
      inline ButtonList(Button *(&buttons)[n]): ButtonList(buttons, n) {}

      /**
       * Create a list of buttons. Makes beginning and handling of a set of
       * buttons easier.
       * 
       * @param buttons The array of buttons to manage together.
       * @param len The number of buttons in the list.
       */
      inline ButtonList(Button **buttons, size_t len)
      : buttons_(buttons), len_(len) {}

      /**
       * Initialise all the buttons. Called from setup() of an Arduino program.
       */
      void begin();

      /**
       * Handle all the buttons. Called in the loop() of an Arduino program to
       * monitor all button states and dispatch any callback events if required.
       */
      void handle();

      /**
       * For CallbackButtons (which each have an id), return a pointer to the
       * first button matching the id (or a null pointer if the id is not
       * found). When using the button, always check if the return value is
       * non-zero.
       * 
       *       Button *btn = btnList.button(id);
       *       if(btn) {
       *         // Use btn...
       *       } else {
       *         // Id not found in list...
       *       }
       * 
       * @return The first id-matching button, or a null pointer.
       */
      Button *button(uint8_t id);

      /**
       * Determine if all of the buttons are currently pressed.
       * 
       * @return True if all pressed, else false.
       */
      bool allPressed();

      /**
       * Determine if any of the buttons are currently pressed.
       * 
       * @return True if any pressed, else false.
       */
      bool anyPressed();

      /**
       * Determine if all of the buttons have been clicked.
       * 
       * @return True if all pressed, else false.
       */
      bool allClicked();

      /**
       * Determine if all of the buttons have been clicked.
       * 
       * @return True if any clicked, else false.
       */
      bool anyClicked();

      /**
       * Reset clicked state of all buttons, returning true if any were clicked.
       * 
       * @return True if any clicked, else false.
       */
      bool resetClicked();

    private:
      Button **buttons_; ///< The array of buttons to manage together.
      size_t len_; ///< The length o the button array.
  };
}
