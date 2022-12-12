/**
 * @file Pins.cpp Implementation of the Pin class and subclasses.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "Pins.h"

uint8_t able::Pin::autoId_ = 0;
uint8_t able::DebouncedPin::debounceTime_ = 50;
uint16_t able::DebouncedPin::heldTime_ = 1000;
uint32_t able::DebouncedPin::idleTime_ = 60000;
uint16_t able::DoubleClickerPin::clickTime_ = 250;
