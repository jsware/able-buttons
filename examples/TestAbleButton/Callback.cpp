/**
 * @file Callback.cpp Definition of the callback functiosn. These functions
 * perform some assertions on the state of the button list and the individual
 * button pressed when a button is pressed. They also set button state flags
 * so the main program can verify button states after hendling the events.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "Callback.h"
#include "Checks.h"
#include "Utils.h"

#if TESTABLE_CALLBACK
  /**
   * Callback function for button events.
   * 
   * @param event The event that has occured.
   * @param id The identifier of the button generating the callback.
   */
  void onEvent(Button::CALLBACK_EVENT event, uint8_t id) {  
    assert(id > 0);
    Button *btn = btnList.button(id); assert(btn == btns[id - 1]);
    ButtonState &state(btnState[id - 1]);

    if(event == Button::BEGIN_EVENT) {
      Serial << F("Event BEGIN_EVENT (") << event << F(") for id ") << id << endl;

      // Assert begin() called once for a button.
      assert(btnState[id - 1].wasStarted == false);
      btnState[id - 1].wasStarted = true; // Set begin for the buttin id.
    } else if(event == Button::PRESSED_EVENT) {
      Serial << F("Event PRESSED_EVENT (") << event << F(") for id ") << id << endl;
      for(size_t i = 0; i < NUM_BUTTONS; ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustPressed(btn);
      state.wasPressed = true;
    } else if(event == Button::RELEASED_EVENT) {
      Serial << F("Event RELEASED_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < NUM_BUTTONS; ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustReleased(btn);
      state.wasReleased = true;
    } else if(event == Button::HELD_EVENT) {
      Serial << F("Event HELD_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(NUM_BUTTONS); ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustHeld(btn);
      state.wasHeld = true;
    } else if(event == Button::IDLE_EVENT) {
      Serial << F("Event IDLE_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(NUM_BUTTONS); ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustIdle(btn);
      state.wasIdle = true;
    } else if(event == Button::SINGLE_CLICKED_EVENT) {
      Serial << F("Event SINGLE_CLICKED_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(NUM_BUTTONS); ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustSingleClicked(btn);
#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        state.wasSingleClicked = true;
        state.resetSingleClicked = true;
#     endif
    } else if(event == Button::DOUBLE_CLICKED_EVENT) {
      Serial << F("Event DOUBLE_CLICKED_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(NUM_BUTTONS); ++i) {
        assert(btnState[i].wasStarted);
      }

      checkButtonJustDoubleClicked(btn);
#     if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
        state.wasDoubleClicked = true;
        state.resetDoubleClicked = true;
#     endif
    } else {
      Serial << F("ERROR: Event UNKNOWN (") << event << F(") for id ") << id << endl;
    }
  }
#endif
