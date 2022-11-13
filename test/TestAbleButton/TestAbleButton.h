/**
 * @file TestAbleButton.h Declarations for the TestAbleButton program. Included
 * by all the modules to share program information.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#pragma once
#define __ASSERT_USE_STDERR
#undef NDEBUG
#include <assert.h>

#include <AbleButtons.h>

// Select the buttons used...
using Button = AblePullupCallbackClickerButton;
using ButtonList = AblePullupCallbackClickerButtonList;

// Forward declarations of callback functions.
void pressedCallback(uint8_t id);
void releasedCallback(uint8_t id);

#define BUTTON_A_PIN 2 ///< Connect button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect button using pulldown resistor circuit.

extern Button *btns[];
extern ButtonList btnList;

extern bool anyReleased;
