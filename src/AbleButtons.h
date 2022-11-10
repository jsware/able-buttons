/**
 * @file AbleButtons.h The main include file for the Arduino Button library
 * Extension (ABLE). Include this file in an Arduino program to access all the
 * available button classes.
 * 
 * It is recommended to then identify which button type is used with code
 * similar to:
 * 
 *     #include <AbleButtons.h>
 *     using Button = AblePullupButton;
 *     using ButtonList = AblePullupButtonList;
 *     ...
 *     Button btn(BUTTON_PIN);
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "button.h"
#include "btnlist.h"
#include "callback.h"

/**
 * AblePulldownButton provides basic button is-pressed capability for buttons
 * connected using pull-down resistor circuits. Button presses are debounced to
 * provide a reliable push/released signal.
 */
using AblePulldownButton = able::Button<able::PulldownResistorCircuit, able::DebouncedPin>;

/**
 * AblePulldownCallbackButton extends the basic debouced button with callbacks
 * on pressed and on released events. When the button is pressed, a user-
 * supplied on-pressed function can be called with the id of the button. The
 * id can be used with the AblePulldownCallbackButtonList class to retrieve a
 * pointer to the button generating the callback.
 *  
 */
using AblePulldownCallbackButton = able::CallbackButton<able::Button<able::PulldownResistorCircuit, able::DebouncedPin>>; ///< Shorthand for a callback button using a pull-down resistor.
using AblePulldownClickerButton = able::Button<able::PulldownResistorCircuit, able::ClickerPin>; ///< Shorthand for clicker using pull-down resistor circuit.
using AblePulldownCallbackClickerButton = able::CallbackButton<able::Button<able::PulldownResistorCircuit, able::ClickerPin>>; ///< Shorthand for clicker using pull-down resistor circuit.

using AblePulldownButtonList = able::ButtonList<AblePulldownButton>; ///< Handler for list of AblePulldownButton objects.
using AblePulldownCallbackButtonList = able::ButtonList<AblePulldownCallbackButton>; ///< Handler for list of AblePulldownCallbackButton objects.
using AblePulldownClickerButtonList = able::ButtonList<AblePulldownClickerButton>; ///< Handler for list of AblePulldownClicker objects.
using AblePulldownCallbackClickerButtonList = able::ButtonList<AblePulldownCallbackClickerButton>; ///< Handler for list of AblePulldownCallbackClicker objects.

using AblePullupButton = able::Button<able::PullupResistorCircuit, able::DebouncedPin>; ///< Shorthand for button using pull-up resistor circuit.
using AblePullupCallbackButton = able::CallbackButton<able::Button<able::PullupResistorCircuit, able::DebouncedPin>>; ///< Shorthand for a callback button using a pull-up resistor.
using AblePullupClickerButton = able::Button<able::PullupResistorCircuit, able::ClickerPin>; ///< Shorthand for clicker using pull-up resistor circuit.
using AblePullupCallbackClickerButton = able::CallbackButton<able::Button<able::PullupResistorCircuit, able::ClickerPin>>; ///< Shorthand for clicker using pull-up resistor circuit.

using AblePullupButtonList = able::ButtonList<AblePullupButton>; ///< Handler for list of AblePullupButton objects.
using AblePullupCallbackButtonList = able::ButtonList<AblePullupCallbackButton>; ///< Handler for list of AblePullupCallbackButton objects.
using AblePullupClickerButtonList = able::ButtonList<AblePullupClickerButton>; ///< Handler for list of AblePullupClicker objects.
using AblePullupCallbackClickerButtonList = able::ButtonList<AblePullupCallbackClickerButton>; ///< Handler for list of AblePullupCallbackClicker objects.
