/**
 * @file TestButton.ino
 * Test Arduino Button Library Extension (ABLE). This program will periodically
 * output "Looping..." to the Serial port. As you press buttons connected to
 * pins 2 and 3 it will assert the button settings in the callback fuctions.
 * 
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#define __ASSERT_USE_STDERR
#undef NDEBUG
#include <assert.h>

#include <AbleButtons.h>
#include "utils.h"

// Select the buttons used...
using Button = AbleButton;//AblePullupCallbackClickerButton;
using ButtonList = AbleButtonList;//AblePullupCallbackClickerButtonList;

// Forward declarations of callback functions.
void pressedCallback(uint8_t id);
void releasedCallback(uint8_t id);

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button using pulldown resistor circuit.

Button btnA(BUTTON_A_PIN, INPUT_PULLUP, pressedCallback, releasedCallback);
Button btnB(BUTTON_B_PIN, INPUT_PULLUP, pressedCallback, releasedCallback);
Button *btns[] = { ///< Array of buttons for ButtonList.
  &btnA,
  &btnB
};
ButtonList btnList(btns); ///< List of buttons.

static bool anyReleased; ///< Flag indicating releasedCallback was called.

/**
 * Setup the PushBtn example. Called once to initialise everything.
 */
void setup() {
  Serial.begin(115200);
  btnList.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Control TestButton. Called repeatedly in a loop.
 */
void loop() {
  static uint16_t count = 0; ///< Counter to preiodically print OK message.
  if(!count++) Serial.println(F("Looking OK..."));

  btnList.handle();
  digitalWrite(LED_BUILTIN, btnList.anyPressed());

  if(anyReleased) {
    assert(btnList.allClicked() == false);
    assert(btnList.anyClicked() == true);
    assert(btnList.resetClicked() == true);
    assert(btnList.anyClicked() == false);
    anyReleased = false;
  } else {
    assert(btnList.allPressed() == false);
    assert(btnList.allClicked() == false);
    assert(btnList.anyClicked() == false);
  }
}

/**
 * Callback function for button pressed.
 * 
 * @param id The identifier of the button generating the callback.
 */
void pressedCallback(uint8_t id) {
  assert(id > 0);
  Button *btn = btnList.button(id); assert(btn == btns[id - 1]);

  assert(btnList.allPressed() == false);

  if(btn) {
    assert(btn->isPressed() == true);
    assert(btn->isClicked() == false);
  } else {
    assert(false);
  }
}

/**
 * Callback function for button released.
 * 
 * @param id The identifier of the button generating the callback.
 */
void releasedCallback(uint8_t id) {
  assert(id > 0);
  Button *btn = btnList.button(id); assert(btn == btns[id - 1]);

  assert(btnList.allPressed() == false);
  assert(btnList.anyPressed() == false);
  assert(btnList.anyClicked() == true);
  if(btn) {
    assert(btn->isPressed() == false);
    assert(btn->isClicked() == true);
    anyReleased = true;
  } else {
    assert(false);
  }
}
