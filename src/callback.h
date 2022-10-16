/**
 * @file
 * Definitions of different button types. Supports pull-up and pull-down
 * resistor configurations. Used as a template parameter to the BasicButton
 * class so different pull-up or pull-down resistor configurations return true
 * or false for isPressed().
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#ifndef INCLUDED_CALLBACK_H
#define INCLUDED_CALLBACK_H
#include <Arduino.h>

namespace jsware {
    /**
     * Return the next auto-assigned button identifier.
     * 
     * @return The next auto-assigned button identifier. Each call increases the
     *         auto-assigned identifier.
     */
    uint8_t autoId();
}

#endif /* INCLUDED_CALLBACK_H */
