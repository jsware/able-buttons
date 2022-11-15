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

// Select the buttons used...
using Button = AblePullupCallbackClickerButton; ///< Using clicker callback pull-up button.
using ButtonList = AblePullupCallbackClickerButtonList; ///< Using clicker callback pull-up button list.

// Forward declarations of callback functions.
void onEvent(Button::CALLBACK_EVENT, uint8_t);
void onPressed(Button *);
void onReleased(Button *);

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button using pulldown resistor circuit.

extern Button *btns[];
extern ButtonList btnList; ///< Declaration of button list.

extern bool anyReleased;
