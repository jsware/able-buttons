/**
 * @file
 * Button state definitions.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_BTNSTATE_H
#define INCLUDED_BTNSTATE_H

namespace jsware {
    /**
     * Define possible states of a button.
     */
    enum ButtonState {
      NONE = 0, ///< Default button state.
      PRESSED = 1, ///< Button is pressed.
      CLICKED = 2 ///< Button was clicked (pressed and released).
    };
}

#endif /* INCLUDED_BTNSTATE_H */
