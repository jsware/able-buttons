/**
 * @file Callback.h Declarations for Callback module.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#pragma once
#include "Config.h"

//
// Forward declarations of callback functions.
//
#if TESTABLE_CALLBACK
void onEvent(Button::CALLBACK_EVENT, uint8_t);
#endif
