/**
 * @file TestAbleButton.h Declarations for the TestAbleButton program. Included
 * by all the modules to share program information.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#pragma once
#define __ASSERT_USE_STDERR ///< Used by <assert.h> to indicate custom assert output
#undef NDEBUG
#include <assert.h>

#include <AbleButtons.h>

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

// Select the buttons used...
// using Button = AblePulldownCallbackClickerButton; ///< Using clicker callback pull-up button.
// using ButtonList = AblePulldownCallbackClickerButtonList; ///< Using clicker callback pull-up button list.
using Button = AblePullupCallbackClickerButton; ///< Using clicker callback pull-up button.
using ButtonList = AblePullupCallbackClickerButtonList; ///< Using clicker callback pull-up button list.

// Forward declarations of callback functions.
void onEvent(Button::CALLBACK_EVENT, uint8_t);
void onPressed(Button *);
void onReleased(Button *);
void onHeld(Button *);
void onIdle(Button *);

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button using pulldown resistor circuit.

extern Button *btns[];
extern ButtonList btnList; ///< Declaration of button list.

extern bool anyReleased;
