/**
 * @file Config.h Declarations to select which buttons we use. Change the
 * circuit, callback and class values to test different classes.
 * 
 * @copyright Copyright (c) 2022 John Scott
 */
#pragma once
#include <AbleButtons.h>

//
// Change these values based on pin connections...
//
#define NUM_BUTTONS 2 ///< The number of buttons to connect for testing.
#define BUTTON_A_PIN 2 ///< Connect first button between this pin and ground.
#define BUTTON_B_PIN 3 ///< Connect second button between this pin and ground.

//
// Change these values to test different combinations...
//

/// 0 = Pulldown; 1 = Pullup
#define TESTABLE_CIRCUIT 1
/// 0 = No Callback; 1 = Callback.
#define TESTABLE_CALLBACK 1
/// 0 = DirectButton; 1 = Button; 2 = ClickerButton; 3 = DoubleClickerButton
#define TESTABLE_CLASS 3


//
// Helper macros to make button identification...
//

/// Set TESTABLE_CIRCUIT to this value to test pulldown circuits.
#define TESTABLE_PULLDOWN 0
/// Set TESTABLE_CIRCUIT to this value to test pullup circuits.
#define TESTABLE_PULLUP 1

/// Set TESTABLE_CLASS to this value to test Able...DirectButton
#define TESTABLE_DIRECT 0
/// Set TESTABLE_CLASS to this value to test Able...Button
#define TESTABLE_BUTTON 1
/// Set TESTABLE_CLASS to this value to test Able...ClickerButton
#define TESTABLE_CLICKER 2
/// Set TESTABLE_CLASS to this value to test Able...DoubleClickerButton
#define TESTABLE_DOUBLECLICKER 3


//
// Configure which Button and ButtonList...
//
#if TESTABLE_CIRCUIT == TESTABLE_PULLUP
# if TESTABLE_CALLBACK
#   if TESTABLE_CLASS == TESTABLE_BUTTON
#     define TESTABLE_USING_BUTTON AblePullupCallbackButton
#     define TESTABLE_USING_BUTTONLIST AblePullupCallbackButtonList
#   elif TESTABLE_CLASS == TESTABLE_CLICKER
#     define TESTABLE_USING_BUTTON AblePullupCallbackClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePullupCallbackClickerButtonList
#   elif TESTABLE_CLASS == TESTABLE_DOUBLECLICKER
             /// Using Button to test
#     define TESTABLE_USING_BUTTON AblePullupCallbackDoubleClickerButton
             /// Using ButtonList to test
#     define TESTABLE_USING_BUTTONLIST AblePullupCallbackDoubleClickerButtonList
#   else
#     define TESTABLE_USING_BUTTON Unsupported
#     define TESTABLE_USING_BUTTONLIST Unsupported
#   endif /* TESTABLE_CLASS */
# else /* Not TESTABLE_CALLBACK */
#   if TESTABLE_CLASS == TESTABLE_DIRECT
#     define TESTABLE_USING_BUTTON AblePullupDirectButton
#     define TESTABLE_USING_BUTTONLIST AblePullupDirectButtonList
#   elif TESTABLE_CLASS == TESTABLE_BUTTON
#     define TESTABLE_USING_BUTTON AblePullupButton
#     define TESTABLE_USING_BUTTONLIST AblePullupButtonList
#   elif TESTABLE_CLASS == TESTABLE_CLICKER
#     define TESTABLE_USING_BUTTON AblePullupClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePullupClickerButtonList
#   elif TESTABLE_CLASS == TESTABLE_DOUBLECLICKER
#     define TESTABLE_USING_BUTTON AblePullupDoubleClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePullupDoubleClickerButtonList
#   else
#     define TESTABLE_USING_BUTTON Unsupported
#     define TESTABLE_USING_BUTTONLIST Unsupported
#   endif /* TESTABLE_CLASS */
# endif /* TESTABLE_CALLBACK */
#elif TESTABLE_CIRCUIT == TESTABLE_PULLDOWN
# if TESTABLE_CALLBACK
#   if TESTABLE_CLASS == TESTABLE_BUTTON
#     define TESTABLE_USING_BUTTON AblePulldownCallbackButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownCallbackButtonList
#   elif TESTABLE_CLASS == TESTABLE_CLICKER
#     define TESTABLE_USING_BUTTON AblePulldownCallbackClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownCallbackClickerButtonList
#   elif TESTABLE_CLASS == TESTABLE_DOUBLECLICKER
#     define TESTABLE_USING_BUTTON AblePulldownCallbackDoubleClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownCallbackDoubleClickerButtonList
#   else
#     define TESTABLE_USING_BUTTON Unsupported
#     define TESTABLE_USING_BUTTONLIST Unsupported
#   endif /* TESTABLE_CLASS */
# else /* Not TESTABLE_CALLBACK */
#   if TESTABLE_CLASS == TESTABLE_DIRECT
#     define TESTABLE_USING_BUTTON AblePulldownDirectButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownDirectButtonList
#   elif TESTABLE_CLASS == TESTABLE_BUTTON
#     define TESTABLE_USING_BUTTON AblePulldownButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownButtonList
#   elif TESTABLE_CLASS == TESTABLE_CLICKER
#     define TESTABLE_USING_BUTTON AblePulldownClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownClickerButtonList
#   elif TESTABLE_CLASS == TESTABLE_DOUBLECLICKER
#     define TESTABLE_USING_BUTTON AblePulldownDoubleClickerButton
#     define TESTABLE_USING_BUTTONLIST AblePulldownDoubleClickerButtonList
#   else
#     define TESTABLE_USING_BUTTON Unsupported
#     define TESTABLE_USING_BUTTONLIST Unsupported
#   endif /* TESTABLE_CLASS */
# endif /* TESTABLE_CALLBACK */
#else
# define TESTABLE_USING_BUTTON Unsupported
# define TESTABLE_USING_BUTTONLIST Unsupported
#endif /* TESTABLE_CIRCUIT */

using Button = TESTABLE_USING_BUTTON; ///< Using the button defined by the circuit, callback and class.
using ButtonList = TESTABLE_USING_BUTTONLIST; ///< Using the button list defined by the circuit, callback and class.

//
// Definitions of global variables...
//
extern Button btnA; ///< Button A
extern Button btnB; ///< Button B
extern Button *btns[]; ///< Array of buttons A and B
extern ButtonList btnList; ///< Declaration of button list.
