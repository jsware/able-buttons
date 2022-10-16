/**
 * @file
* Callback button helpers.
 * 
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "callback.h"

namespace jsware {
  static uint8_t autoId_ = 0; ///< Auto-assigned button idedtifier.

  uint8_t autoId() {
    return ++autoId_;
  }
}
