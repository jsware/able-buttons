/**
 * @file TestAbleButton.h Declarations for the TestAbleButton program. Included
 * by all the modules to share program information.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#pragma once
#include <AbleButtons.h>
#include "Config.h"

extern void __assert(const char *__func, const char *__file, int __lineno, const __FlashStringHelper *__sexp);

/// Macro to assert using FlashStringHelper to reduce memory usage.
#define assert(e) ((e) ? (void)0 : __assert(__func__, __FILE__, __LINE__, F(#e)))

/**
 * Output a specific type to the Print stream.
 * 
 * @param p The print-stream to output to.
 * @param o The object to output.
 * 
 * @returns The print-stream object (allows chaining of << operators - as in
 *          `Serial << x << y << z;`).
 */
template<typename T>
inline Print &operator<<(Print &p, const T o) { p.print(o); return p; }

/// Special type to allow `Serial << endl` to print a line and flush the stream.
enum endl {
  endl ///< The special value of endl  triggers the Serial.println() and Serial.flush().
};

/**
 * Special stream operator for turning Serial << endl into new line and stream flush.
 * 
 * @param p The print-stream to output a new line and flush.
 * @param endl The special `endl` enumeration type
 * 
 * @returns The print-stream object (allows chaining of << operators - as in
 *          `Serial << x << y << z;`).
 */
inline Print &operator <<(Print &p, enum endl) { p.println(); p.flush(); return p; }

using Button = TESTABLE_USING_BUTTON; ///< Using the button defined by the circuit, callback and class.
using ButtonList = TESTABLE_USING_BUTTONLIST; ///< Using the button list defined by the circuit, callback and class.

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button using pulldown resistor circuit.

struct ButtonState {
  bool isPressed;
  bool isHeld;
  bool isIdle;
#if TESTABLE_CLASS >= TESTABLE_CLICKER
  bool isClicked;
#endif
#if TESTABLE_CLASS >= TESTABLE_DOUBLECLICKER
  bool isDoubleClicked;
#endif
};

//
// Forward declarations of callback functions.
//
#if TESTABLE_CALLBACK
void onEvent(Button::CALLBACK_EVENT, uint8_t);
#endif
void onPressed(Button *);
void onReleased(Button *);
void onHeld(Button *);
void onIdle(Button *);

//
// Definitions of Button checks...
//
void checkButtonSetup(Button *btn);
void checkButtonJustPressed(Button *btn);
void checkButtonJustReleased(Button *btn);
void checkButtonJustHeld(Button *btn);
void checkButtonJustIdle(Button *btn);
void checkButtonJustClicked(Button *btn);
void checkButtonJustDoubleClicked(Button *btn);
void checkButtonIntegrity(Button *btn, ButtonState &state);
void displayButton(Button *btn, ButtonState &state, int index);

//
// Definitions of ButtonList checks...
//
void checkButtonListSetup();
void checkButtonListJustPressed(Button *btnPressed);
void checkButtonListJustReleased(Button *btnReleased);
void checkButtonListJustHeld(Button *btn);
void checkButtonListJustIdle(Button *btn);
void checkButtonListJustClicked(Button *btn);
void checkButtonListJustDoubleClicked(Button *btn);
void checkButtonListIntegrity();

//
// Definitions of global variables...
//
extern Button btnA; ///< Button A
extern Button btnB; ///< Button B
extern Button *btns[]; ///< Array of buttons A and B
extern ButtonList btnList; ///< Declaration of button list.
extern Button *pressedBtn; ///< Button pressed event.
extern Button *releasedBtn; ///< Button released event.
