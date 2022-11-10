# Arduino Button Library Extension

The Arduino Button Library Extension (ABLE) is a simple, lightweight button library to capture input from buttons connected to your Arduino. For example, the Arduino Debounce examples program uses 1,116 bytes of program storage and 19 bytes of dynamic memory.


# Introduction

AbleButtons have increasing capabilities chosen at compile-time without unnecessarily including unused button functionality. For example, if you do not use callback functions, choosing the right button reduces your program's size giving you more space for your project's purpose.

All buttons support [button debouncing](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce). Button debouncing addresses [contact bounce](https://en.wikipedia.org/wiki/Switch#Contact_bounce) (aka chatter) common to mechanical buttons in electronic circuits. Debouncing a button waits for a steady contact so the button does not appear to bounce between open and closed.

AbleButtons support circuits using pull-up and pull-down resistors. This includes the internal pull-up resistors on various Arduino microcontrollers. The internal pull-up resistors make it easy to connect an Arduino pin to ground through a button or switch.

The simplest AbleButton identifies when it is pressed or released.

AbleButtons supports clicks. A clicker remembers it has been pressed and released to complete a click. Your program can respond to a complete click (a press followed by release), rather than a simple press.

AbleButtons supports callback functions. When the button is pressed and released, a function can be called for that event.

For programs with several buttons, AbleButtons provides a button list feature. A program can define a list of buttons and then manage them together. Buttons still work independently (each has its own pressed, clicked and callback settings).

# Buttons

The following button combinations are available from AbleButtons:

| Using                             | Resistor | Pin   | Callback? |
| :-------------------------------- | :------: | :---: | :-------: |
| AblePulldownButton                | Pulldown | Push  | No        |
| AblePulldownCallbackButton        | Pulldown | Push  | Yes       |
| AblePulldownClickerButton         | Pulldown | Click | No        |
| AblePulldownCallbackClickerButton | Pulldown | Click | Yes       |
| AblePullupButton                  | Pull-up  | Push  | No        |
| AblePullupCallbackButton          | Pull-up  | Push  | Yes       |
| AblePullupClickerButton           | Pull-up  | Click | No        |
| AblePullupCallbackClickerButton   | Pull-up  | Click | Yes       |


Choosing a button type is as simple as declaring which button your program uses:

```c
#include <AbleButtons.h>

#define PIN_A 2
#define PIN_A 3

using Button = AblePullupClickerButton;
using ButtonList = AblePullupClickerButtonList;

Button btnA(PIN_A);
Button btnB(PIN_B);

void begin() {
  btnA.begin();
  btnB.begin();
}

void loop() {
  btnA.handle();
  btnB.handle();

  digitalWrite(BUILTIN_LED_PIN, btnA.isPressed() || btnB.isPressed());
}
```

It is recommended to use the same button type for all your buttons, even if you are not using all features on all your buttons. For example, if you have one button using a simple isPressed() check and another button needs a isClicked() check, it's better to define it like this to reduce program-spave usage:

```c
#include <AbleButtons.h>

using Button = AblePullupClickerButton;
using ButtonList = AblePullupClickerButtonList;

Button btnA(PIN_A);
Button btnB(PIN_B);

void begin() {
  btnA.begin();
  btnB.begin();
}

void loop() {
  btnA.handle();
  btnB.handle();

  digitalWrite(BUILTIN_LED_PIN, btnA.isPressed() || btnB.isPressed());
}
```
