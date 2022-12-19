/**
 * @file Callback.cpp Definition of the callback function. This
 * function performs some assertions on the state of the button list and the
 * individual button pressed when a button is pressed.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#include "TestAbleButton.h"

static bool begin[] = {
  false,
  false
};

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

    if(event == Button::BEGIN_EVENT) {
      Serial << F("Event BEGIN_EVENT (") << event << F(") for id ") << id << endl;

      // Assert begin() called once for a button.
      assert(begin[id - 1] == false);
      begin[id - 1] = true; // Set begin for the buttin id.
    } else if(event == Button::PRESSED_EVENT) {
      Serial << F("Event PRESSED_EVENT (") << event << F(") for id ") << id << endl;
      for(size_t i = 0; i < sizeof(begin); ++i) {
        assert(begin[i]);
      }

      onPressed(btn);
    } else if(event == Button::RELEASED_EVENT) {
      Serial << F("Event RELEASED_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(begin); ++i) {
        assert(begin[i]);
      }

      onReleased(btn);
    } else if(event == Button::HELD_EVENT) {
      Serial << F("Event HELD_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(begin); ++i) {
        assert(begin[i]);
      }

      onHeld(btn);
    } else if(event == Button::IDLE_EVENT) {
      Serial << F("Event IDLE_EVENT (") << event << F(") for id ") << id << endl;

      for(size_t i = 0; i < sizeof(begin); ++i) {
        assert(begin[i]);
      }

      onIdle(btn);
    } else {
      Serial << F("ERROR: Event UNKNOWN (") << event << F(") for id ") << id << endl;
    }
  }
#endif
