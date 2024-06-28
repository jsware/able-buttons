/**
 * @file AbleButtons.h The main include file for the Arduino Button library
 * Extension (ABLE). Include this file in an Arduino program to access all the
 * available button classes.
 * 
 * It is recommended to then identify which button type is used with code
 * similar to:
 * 
 *     #include <AbleButtons.h>
 *     ...
 *     using Button = AblePullupButton;
 *     using ButtonList = AblePullupButtonList;
 *     ...
 *     Button btn(BUTTON_PIN);
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#pragma once
#include "Button.h"
#include "ButtonList.h"
#include "CallbackButton.h"

//
// Pulldown buttons...
//

/**
 * AblePulldownButton provides basic button is-pressed capability for buttons
 * connected using pulldown resistor circuits. Button presses are debounced to
 * provide a reliable push/released signal.
 */
using AblePulldownButton = able::Button<able::PulldownResistorCircuit, able::DebouncedPin>;

/**
 * AblePulldownCallbackButton extends the basic debouced button with callbacks
 * on pressed and on released events. When the button is pressed, a user-
 * supplied on-pressed function can be called with the id of the button. The
 * id can be used with the AblePulldownCallbackButtonList class to retrieve a
 * pointer to the button generating the callback. Similarly, when the button is
 * released, a user-supplied on-released function can be called.  
 */
using AblePulldownCallbackButton = able::CallbackButton<able::Button<able::PulldownResistorCircuit, able::DebouncedPin>>; ///< Shorthand for a callback button using a pulldown resistor.

/**
 * AblePulldownClickerButton provides additional button-click capability to the
 * is-pressed capability of a basic button. A button click is a button-press,
 * followed by a button-release. As with basic button capabilities, button
 * presses are debounced to provide a reliable push/released signal.
 */
using AblePulldownClickerButton = able::Button<able::PulldownResistorCircuit, able::ClickerPin>;

/**
 * AblePulldownCallbackClickerButton provides callback capability to a clicker
 * button. A button click is a button-press, followed by a button-release. It
 * also extends the button with callbacks on pressed and on released events.
 * When the button is pressed, a user-supplied on-pressed function can be called
 * with the id of the button. The id can be used with the
 * AblePulldownCallbackClickerButtonList class to retrieve a pointer to the
 * clicker button generating the callback. Similarly, when the button is
 * released, a user-supplied on-released function can be called. As with basic
 * button capabilities, button presses are debounced to provide a reliable push/
 * released signal.
 */
using AblePulldownCallbackClickerButton = able::CallbackButton<able::Button<able::PulldownResistorCircuit, able::ClickerPin>>;

/**
 * AblePulldownDirectButton provides basic button is-pressed capability for
 * buttons connected using pulldown resistor circuits. Button presses are
 * **not** debounced so provide potentially unreliable push/released signals
 * when pressed or released due to contact bouncing.
 */
using AblePulldownDirectButton = able::Button<able::PulldownResistorCircuit, able::Pin>;

/**
 * AblePulldownDoubleClickerButton provides additional double-click capability to
 * the is-clicked capability of a clicker button. A button double-click is a
 * second click (button-press, followed by a button-release) within the double-
 * click time. As with other button capabilities, button presses are debounced
 * to provide a reliable push/released signal.
 */
using AblePulldownDoubleClickerButton = able::Button<able::PulldownResistorCircuit, able::DoubleClickerPin>;

/**
 * AblePulldownCallbackDoubleClickerButton provides additional double-click
 * capability to the is-clicked capability of a clicker button. A button double-
 * click is a second click (button-press, followed by a button-release) within
 * the double-click time. As with other button capabilities, button presses are
 * debounced to provide a reliable push/released signal.
 */
using AblePulldownCallbackDoubleClickerButton = able::CallbackClickerButton<able::CallbackButton<able::Button<able::PulldownResistorCircuit, able::DoubleClickerPin>>>;

//
// Pulldown button lists...
//

/**
 * AblePulldownButtonList allows an array of AblePulldownButton objects to be
 * managed together. Rather than calling begin() and handle() methods for each
 * button, call the begin() and handle() method of the button list object, which
 * calls the begin() and handle() methods of each button in the list. 
 */
using AblePulldownButtonList = able::ButtonList<AblePulldownButton>;

/**
 * AblePulldownButtonList allows an array of AblePulldownButton objects
 * to be managed together. Rather than calling begin() and handle() methods for
 * each button, call the begin() and handle() method of the button list object,
 * which calls the begin() and handle() methods of each button in the list. 
 */
using AblePulldownButtonList = able::ButtonList<AblePulldownButton>;

/**
 * AblePulldownCallbackButtonList allows an array of AblePulldownCallbackButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePulldownCallbackButtonList = able::ButtonList<AblePulldownCallbackButton>;

/**
 * AblePulldownClickerButtonList allows an array of AblePulldownClickerButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePulldownClickerButtonList = able::ButtonList<AblePulldownClickerButton>;

/**
 * AblePulldownCallbackClickerButtonList allows an array of
 * AblePulldownCallbackClickerButton objects to be managed together. Rather than
 * calling begin() and handle() methods for each button, call the begin() and
 * handle() method of the button list object, which calls the begin() and
 * handle() methods of each button in the list. 
 */
using AblePulldownCallbackClickerButtonList = able::ButtonList<AblePulldownCallbackClickerButton>;

/**
 * AblePulldownDirectButtonList allows an array of AblePulldownDirectButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePulldownDirectButtonList = able::ButtonList<AblePulldownDirectButton>;

/**
 * AblePulldownDoubleClickerButtonList allows an array of AblePulldownDoubleClickerButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePulldownDoubleClickerButtonList = able::ButtonList<AblePulldownDoubleClickerButton>;

/**
 * AblePulldownCallbackDoubleClickerButtonList allows an array of
 * AblePulldownCallbackDoubleClickerButton objects to be managed together. Rather
 * than calling begin() and handle() methods for each button, call the begin()
 * and handle() method of the button list object, which calls the begin() and
 * handle() methods of each button in the list. 
 */
using AblePulldownCallbackDoubleClickerButtonList = able::ButtonList<AblePulldownCallbackDoubleClickerButton>;

//
// Pull-up buttons...
//

/**
 * AblePullupButton provides basic button is-pressed capability for buttons
 * connected using pull-up resistor circuits. Button presses are debounced to
 * provide a reliable push/released signal.
 */
using AblePullupButton = able::Button<able::PullupResistorCircuit, able::DebouncedPin>;

/**
 * AblePullupCallbackButton extends the basic debouced button with callbacks
 * on pressed and on released events. When the button is pressed, a user-
 * supplied on-pressed function can be called with the id of the button. The
 * id can be used with the AblePullupCallbackButtonList class to retrieve a
 * pointer to the button generating the callback. Similarly, when the button is
 * released, a user-supplied on-released function can be called.  
 */
using AblePullupCallbackButton = able::CallbackButton<able::Button<able::PullupResistorCircuit, able::DebouncedPin>>; ///< Shorthand for a callback button using a pulldown resistor.

/**
 * AblePullupClickerButton provides additional button-click capability to the
 * is-pressed capability of a basic button. A button click is a button-press,
 * followed by a button-release. As with basic button capabilities, button
 * presses are debounced to provide a reliable push/released signal.
 */
using AblePullupClickerButton = able::Button<able::PullupResistorCircuit, able::ClickerPin>;

/**
 * AblePullupCallbackClickerButton provides callback capability to a clicker
 * button. A button click is a button-press, followed by a button-release. It
 * also extends the button with callbacks on pressed and on released events.
 * When the button is pressed, a user-supplied on-pressed function can be called
 * with the id of the button. The id can be used with the
 * AblePullupCallbackClickerButtonList class to retrieve a pointer to the
 * clicker button generating the callback. Similarly, when the button is
 * released, a user-supplied on-released function can be called. As with basic
 * button capabilities, button presses are debounced to provide a reliable push/
 * released signal.
 */
using AblePullupCallbackClickerButton = able::CallbackButton<able::Button<able::PullupResistorCircuit, able::ClickerPin>>; ///< Shorthand for clicker using pulldown resistor circuit.

/**
 * AblePullupDirectButton provides basic button is-pressed capability for
 * buttons connected using pull-up resistor circuits. Button presses are **not**
 * debounced so provide potentially unreliable push/released signals when
 * pressed or released due to contact bouncing.
 */
using AblePullupDirectButton = able::Button<able::PullupResistorCircuit, able::Pin>;

/**
 * AblePullupDoubleClickerButton provides additional double-click capability to
 * the is-clicked capability of a clicker button. A button double-click is a
 * second click (button-press, followed by a button-release) within the double-
 * click time. As with other button capabilities, button presses are debounced
 * to provide a reliable push/released signal.
 */
using AblePullupDoubleClickerButton = able::Button<able::PullupResistorCircuit, able::DoubleClickerPin>;

/**
 * AblePullupCallbackDoubleClickerButton provides additional double-click capability to
 * the is-clicked capability of a clicker button. A button double-click is a
 * second click (button-press, followed by a button-release) within the double-
 * click time. As with other button capabilities, button presses are debounced
 * to provide a reliable push/released signal.
 */
using AblePullupCallbackDoubleClickerButton = able::CallbackClickerButton<able::CallbackButton<able::Button<able::PullupResistorCircuit, able::DoubleClickerPin>>>;

//
// Pull-up button lists...
//

/**
 * AblePullupButtonList allows an array of AblePullupButton objects to be
 * managed together. Rather than calling begin() and handle() methods for each
 * button, call the begin() and handle() method of the button list object, which
 * calls the begin() and handle() methods of each button in the list. 
 */
using AblePullupButtonList = able::ButtonList<AblePullupButton>; ///< Handler for list of AblePullupButton objects.

/**
 * AblePullupCallbackButtonList allows an array of AblePullupCallbackButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePullupCallbackButtonList = able::ButtonList<AblePullupCallbackButton>;

/**
 * AblePullupClickerButtonList allows an array of AblePullupClickerButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePullupClickerButtonList = able::ButtonList<AblePullupClickerButton>;

/**
 * AblePullupCallbackClickerButtonList allows an array of
 * AblePullupCallbackClickerButton objects to be managed together. Rather than
 * calling begin() and handle() methods for each button, call the begin() and
 * handle() method of the button list object, which calls the begin() and
 * handle() methods of each button in the list. 
 */
using AblePullupCallbackClickerButtonList = able::ButtonList<AblePullupCallbackClickerButton>; ///< Handler for list of AblePulldownCallbackClicker objects.

/**
 * AblePullupDirectButtonList allows an array of AblePullupDirectButton objects
 * to be managed together. Rather than calling begin() and handle() methods for
 * each button, call the begin() and handle() method of the button list object,
 * which calls the begin() and handle() methods of each button in the list. 
 */
using AblePullupDirectButtonList = able::ButtonList<AblePullupDirectButton>;

/**
 * AblePullupDoubleClickerButtonList allows an array of AblePullupDoubleClickerButton
 * objects to be managed together. Rather than calling begin() and handle()
 * methods for each button, call the begin() and handle() method of the button
 * list object, which calls the begin() and handle() methods of each button in
 * the list. 
 */
using AblePullupDoubleClickerButtonList = able::ButtonList<AblePullupDoubleClickerButton>;

/**
 * AblePullupCallbackDoubleClickerButtonList allows an array of
 * AblePullupCallbackDoubleClickerButton objects to be managed together. Rather
 * than calling begin() and handle() methods for each button, call the begin()
 * and handle() method of the button list object, which calls the begin() and
 * handle() methods of each button in the list. 
 */
using AblePullupCallbackDoubleClickerButtonList = able::ButtonList<AblePullupCallbackDoubleClickerButton>;
