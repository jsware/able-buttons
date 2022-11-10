/**
 * @file AbleButtons.cpp Implementation of
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include <ablelist.h>

void AbleButtonList::begin() {
  for(size_t i = 0; i < len_; ++i) {
    buttons_[i]->begin();
  }
}


void AbleButtonList::handle() {
  for(size_t i = 0; i < len_; ++i) {
    buttons_[i]->handle();
  }
}


AbleButton *AbleButtonList::button(uint8_t id) {
  AbleButton *rc = 0;
  for(size_t i = 0; i < len_; ++i) {
    if(buttons_[i]->id() == id ) {
      rc = buttons_[i];
      break;
    }
  }
  return rc;
}

bool AbleButtonList::allPressed() {
  bool rc = true;
  for(size_t i = 0; i < len_; ++i) {
    if(!buttons_[i]->isPressed()) {
      rc = false;
    }
  }
  return rc;
}

bool AbleButtonList::anyPressed() {
  bool rc = false;
  for(size_t i = 0; i < len_; ++i) {
    if(buttons_[i]->isPressed()) {
      rc = true;
    }
  }
  return rc;
}

bool AbleButtonList::allClicked() {
  bool rc = true;
  for(size_t i = 0; i < len_; ++i) {
    if(!buttons_[i]->isClicked()) {
      rc = false;
    }
  }
  return rc;
}

bool AbleButtonList::anyClicked() {
  bool rc = false;
  for(size_t i = 0; i < len_; ++i) {
    if(buttons_[i]->isClicked()) {
      rc = true;
    }
  }
  return rc;
}

bool AbleButtonList::resetClicked() {
  bool rc = false;
  for(size_t i = 0; i < len_; ++i) {
    if(buttons_[i]->resetClicked()) {
      rc = true;
    }
  }
  return rc;
}
