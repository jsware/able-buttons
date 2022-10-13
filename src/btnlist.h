/**
 * @file
 * Definitions of a button list. ButtonList allows an array of buttons to be
 * controlled via a single begin() and handle() calls. Useful for programs that
 * use multiple buttons.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_BTNLIST_H
#define INCLUDED_BTNLIST_H
#include <stddef.h>

namespace jsware {
  /**
   * Template for a list of buttons of the same type. Allows a set of buttons
   * to be controlled together. NB: You cannot mix buttons in the same list (use
   * separate lists).
   */
  template <typename Button>
  class TButtonList {
    public:
      /**
       * Create a list of buttons. Makes beginning and handling of a set of
       * buttons easier.
       * 
       * @param buttons The array of buttons to manage together.
       */
      template <size_t n>
      TButtonList(Button (&buttons)[n]): TButtonList(buttons, n) {}

      /**
       * Create a list of buttons. Makes beginning and handling of a set of
       * buttons easier.

       * @param buttons The array of buttons to manage together.
       * @param len The number of buttons in the list.
       */
      TButtonList(Button *buttons, size_t len)
      : buttons_(buttons)
      , len_(len) {}

      /**
       * Initialise all the buttons. Called from setup() of an Arduino program.
       */
      void begin() {
        for(size_t i = 0; i < len_; ++i) {
            buttons_[i].begin();
        }
      }

      /**
       * Handle all the buttons. Called in the loop() of an Arduino program to
       * monitor all button states and dispatch any callback events if required.
       */
      void handle() {
        for(size_t i = 0; i < len_; ++i) {
            buttons_[i].handle();
        }
      }

      /**
       * Determine if all of the buttons are currently pressed.
       * 
       * @return True if all pressed, else false.
       */
      bool allPressed() const {
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i].isPressed()) {
            return false;
          }
        }
        return true;
      }

      /**
       * Determine if any of the buttons are currently pressed.
       * 
       * @return True if any pressed, else false.
       */
      bool anyPressed() const {
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i].isPressed()) {
            return true;
          }
        }
        return false;
      }

    private:
      Button *buttons_; ///< The array of buttons to manage together.
      size_t len_; ///< The length o the button array.
  };
}

using BasicButtonList = jsware::TButtonList<BasicButton>; ///< Shorthand form for a list of BasicButtons.
using BasicPullupButtonList = jsware::TButtonList<BasicPullupButton>; ///< Shorthand form for a list of BasicPullupButtons.
using BasicPulldownButtonList = jsware::TButtonList<BasicPulldownButton>; ///< Shorthand form for a list of BasicPulldownButtons.

#endif /* INCLUDED_BTNLIST_H */
