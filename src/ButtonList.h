/**
 * @file ButtonList.h Definitions of the ButtonList templae class. The button
 * list allows an array of buttons to be controlled via a single begin() and
 * handle() pair of methods. Useful for programs that use multiple buttons.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "Button.h"

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
      //
      // Creators...
      //

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

    public:
      //
      // Modifiers...
      //

      /**
       * Initialise all the buttons. Called from setup() of an Arduino program.
       */
      inline void begin() { 
        for(size_t i = 0; i < len_; ++i) {
          buttons_[i]->begin(); 
        } 
      }

      /**
       * Handle all the buttons. Called in the loop() of an Arduino program to
       * monitor all button states and dispatch any callback events if required.
       */
      void handle() {
        for(size_t i = 0; i < len_; ++i) {
          buttons_[i]->handle();
        }
      }

      /**
       * Reset clicked state of all buttons, returning true if any were clicked.
       * 
       * @return True if any clicked, else false.
       */
      bool resetClicked() {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->resetClicked()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Reset double-clicked state of all buttons, returning true if any were
       * double-clicked.
       * 
       * @return True if any double-clicked, else false.
       */
      bool resetDoubleClicked() {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->resetDoubleClicked()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Reset single-clicked state of all buttons, returning true if any were
       * single-clicked.
       * 
       * @return True if any single-clicked, else false.
       */
      bool resetSingleClicked() {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->resetSingleClicked()) {
            rc = true;
          }
        }
        return rc;
      }

    public:
      //
      // Accessors...
      //

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
       * @param id The identifier of the button to find in the list.
       * 
       * @return The first id-matching button, or a null pointer.
       */
      Button *button(uint8_t id) const {
        Button *rc = 0;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->id() == id ) {
            rc = buttons_[i];
            break;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons are currently pressed.
       * 
       * @return True if all pressed, else false.
       */
      bool allPressed() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isPressed()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if any of the buttons are currently pressed.
       * 
       * @return True if any pressed, else false.
       */
      bool anyPressed() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isPressed()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons are currently held.
       * 
       * @return True if all held, else false.
       */
      bool allHeld() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isHeld()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if any of the buttons are currently held.
       * 
       * @return True if any held, else false.
       */
      bool anyHeld() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isHeld()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons are currently idle.
       * 
       * @return True if all idle, else false.
       */
      bool allIdle() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isIdle()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if any of the buttons are currently idle.
       * 
       * @return True if any idle, else false.
       */
      bool anyIdle() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isIdle()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons have been clicked.
       * 
       * @return True if all pressed, else false.
       */
      bool allClicked() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isClicked()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons have been clicked.
       * 
       * @return True if any clicked, else false.
       */
      bool anyClicked() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isClicked()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons have been double-clicked.
       * 
       * @return True if all double-clicked, else false.
       */
      bool allDoubleClicked() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isDoubleClicked()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if any of the buttons have been double-clicked.
       * 
       * @return True if any double-clicked, else false.
       */
      bool anyDoubleClicked() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isDoubleClicked()) {
            rc = true;
          }
        }
        return rc;
      }

      /**
       * Determine if all of the buttons have been single-clicked.
       * 
       * @return True if all single-clicked, else false.
       */
      bool allSingleClicked() const {
        bool rc = true;
        for(size_t i = 0; i < len_; ++i) {
          if(!buttons_[i]->isSingleClicked()) {
            rc = false;
          }
        }
        return rc;
      }

      /**
       * Determine if any of the buttons have been single-clicked.
       * 
       * @return True if any single-clicked, else false.
       */
      bool anySingleClicked() const {
        bool rc = false;
        for(size_t i = 0; i < len_; ++i) {
          if(buttons_[i]->isSingleClicked()) {
            rc = true;
          }
        }
        return rc;
      }

    private:
      //
      // Data...
      //
      Button **buttons_; ///< The array of buttons to manage together.
      size_t len_; ///< The length o the button array.
  };
}
