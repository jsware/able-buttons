/**
 * @file btnlist.cpp
 * Implementations of ButtonList template functions.
 *
 * @copyright Copyright (c) 2022 John Scott.
 */
#include "btnlist.h"
#include "callback.h"

/**
 * Nasty macro hack to avoid duplicating code for a template. 
 */
#define ButtonList_Button__begin(Button, Circuit, Pin) template <> \
  void ButtonList<Button<Circuit, Pin>>::begin() { \
    for(size_t i = 0; i < len_; ++i) { \
      buttons_[i]->begin(); \
    } \
  }

#define ButtonList_Callback__begin(Button, Circuit, Pin) template <> \
  void ButtonList<CallbackButton<Button<Circuit, Pin>>>::begin() { \
    for(size_t i = 0; i < len_; ++i) { \
      buttons_[i]->begin(); \
    } \
  }

#define ButtonList_Button__handle(Button, Circuit, Pin) template <> \
  void ButtonList<Button<Circuit, Pin>>::handle() { \
    for(size_t i = 0; i < len_; ++i) { \
      buttons_[i]->handle(); \
    } \
  }

#define ButtonList_Callback__handle(Button, Circuit, Pin) template <> \
  void ButtonList<CallbackButton<Button<Circuit, Pin>>>::handle() { \
    for(size_t i = 0; i < len_; ++i) { \
      buttons_[i]->handle(); \
    } \
  }

#define ButtonList_Button__button(Button, Circuit, Pin) template <> \
  Button<Circuit, Pin> *ButtonList<Button<Circuit, Pin>>:: \
  button(uint8_t id) { \
    Button<Circuit, Pin> *rc = 0; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->id() == id ) { \
        rc = buttons_[i]; \
        break; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__button(Button, Circuit, Pin) template <> \
  CallbackButton<Button<Circuit, Pin>> *ButtonList<CallbackButton<Button<Circuit, Pin>>>:: \
  button(uint8_t id) { \
    CallbackButton<Button<Circuit, Pin>> *rc = 0; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->id() == id ) { \
        rc = buttons_[i]; \
        break; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button__allPressed(Button, Circuit, Pin) template <> \
  bool ButtonList<Button<Circuit, Pin>>::allPressed() { \
    bool rc = true; \
    for(size_t i = 0; i < len_; ++i) { \
      if(!buttons_[i]->isPressed()) { \
        rc = false; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__allPressed(Button, Circuit, Pin) template <> \
  bool ButtonList<CallbackButton<Button<Circuit, Pin>>>::allPressed() { \
    bool rc = true; \
    for(size_t i = 0; i < len_; ++i) { \
      if(!buttons_[i]->isPressed()) { \
        rc = false; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button__anyPressed(Button, Circuit, Pin) template <> \
  bool ButtonList<Button<Circuit, Pin>>::anyPressed() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->isPressed()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__anyPressed(Button, Circuit, Pin) template <> \
  bool ButtonList<CallbackButton<Button<Circuit, Pin>>>::anyPressed() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->isPressed()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button__allClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<Button<Circuit, Pin>>::allClicked() { \
    bool rc = true; \
    for(size_t i = 0; i < len_; ++i) { \
      if(!buttons_[i]->isClicked()) { \
        rc = false; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__allClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<CallbackButton<Button<Circuit, Pin>>>::allClicked() { \
    bool rc = true; \
    for(size_t i = 0; i < len_; ++i) { \
      if(!buttons_[i]->isClicked()) { \
        rc = false; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button__anyClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<Button<Circuit, Pin>>::anyClicked() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->isClicked()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__anyClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<CallbackButton<Button<Circuit, Pin>>>::anyClicked() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->isClicked()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button__resetClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<Button<Circuit, Pin>>::resetClicked() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->resetClicked()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Callback__resetClicked(Button, Circuit, Pin) template <> \
  bool ButtonList<CallbackButton<Button<Circuit, Pin>>>::resetClicked() { \
    bool rc = false; \
    for(size_t i = 0; i < len_; ++i) { \
      if(buttons_[i]->resetClicked()) { \
        rc = true; \
      } \
    } \
    return rc; \
  }

#define ButtonList_Button(Button, Circuit, Pin) \
  ButtonList_Button__begin(Button, Circuit, Pin) \
  ButtonList_Button__handle(Button, Circuit, Pin) \
  ButtonList_Button__allPressed(Button, Circuit, Pin) \
  ButtonList_Button__anyPressed(Button, Circuit, Pin) \
  ButtonList_Button__allClicked(Button, Circuit, Pin) \
  ButtonList_Button__anyClicked(Button, Circuit, Pin) \
  ButtonList_Button__resetClicked(Button, Circuit, Pin)

#define ButtonList_Callback(Button, Circuit, Pin) \
  ButtonList_Callback__begin(Button, Circuit, Pin) \
  ButtonList_Callback__handle(Button, Circuit, Pin) \
  ButtonList_Callback__button(Button, Circuit, Pin) \
  ButtonList_Callback__allPressed(Button, Circuit, Pin) \
  ButtonList_Callback__anyPressed(Button, Circuit, Pin) \
  ButtonList_Callback__allClicked(Button, Circuit, Pin) \
  ButtonList_Callback__anyClicked(Button, Circuit, Pin) \
  ButtonList_Callback__resetClicked(Button, Circuit, Pin)

namespace able {
  ButtonList_Button(Button, PullupResistorCircuit, DebouncedPin)

  ButtonList_Callback(Button, PullupResistorCircuit, ClickerPin)
}