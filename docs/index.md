---
title: Arduino Button Library Extension (Able)
layout: splash
header:
  overlay_image: /assets/images/buttons.jpg
  overlay_filter: 0.66
  actions:
    - label: "<i class='fas fa-check-square'></i> Introduction"
      url: "#introduction"
    - label: "<i class='fas fa-download'></i> Installation"
      url: "#installation"
    - label: "<i class='fas fa-list-alt'></i> Usage"
      url: "#usage"
    - label: "<i class='fas fa-book'></i> Docs"
      url: "./html"
    - label: "<i class='fab fa-github'></i> View on GitHub"
      url: "https://github.com/jsware/buttons"
  caption: "Photo credit: [**Unsplash**](https://unsplash.com/photos/nhR-ALn6x-o)"
excerpt: >
  A simple, lightweight button library to capture input from buttons connected
  to the Arduino.
---
# Arduino Button Library Extension (Able)

{% include toc title="Contents" %}

# ABLE

The **Arduino Button Library Extension** (Able) is a simple, lightweight button library requiring minimal memory overhead. For example, the `Buttonable` sample has minimal overhead compared to the equivalent [Button](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button) example included with the Arduino IDE. Additionally, the `Debouncable` example uses *less* program storage than the equivalent [Debounce](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce) program provided with the Arduino IDE.

## Introduction

Able provides a suite of button classes so you can choose the best fit for your needs without including unused capabilities. By choosing, at compile time, the features you require, only the code necessary for those features is included.

For example, if you do not use callback functions, choosing the right button without the callback feature reduces your program's size giving you more space for your project's purpose.

This selection is done with `using Button = AbleButton` and `using ButtonList = AbleButtonList` style commands in your program. You must initialise each button with a `begin()` call in your `setup()` function and `handle()` it in your `loop()` function.

```c
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupButton; // Using basic pull-up button.
using ButtonList = AblePullupButtonList; // Using basic pull-up button list.

#define BUTTON_PIN 2 // Connect button between this pin and ground.
Button btn(BUTTON_PIN); // The button to check.

void setup() {
  // put your setup code here, to run once:

  btn.begin(); // Always begin() each button to initialise it.

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  btn.handle(); // Always handle() each button in a loop to use it.

  digitalWrite(LED_BUILTIN, btn.isPressed());
}
```

All AbleButtons support [button debouncing](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce) (with the exception of the direct button). Button debouncing addresses [contact bounce](https://en.wikipedia.org/wiki/Switch#Contact_bounce) common to mechanical buttons in electronic circuits. Debouncing a button waits for a steady contact so the button does not appear to bounce between open and closed. You can control the debounce wait-time for a steady contact, but the default value is usually sufficient.

All AbleButtons (including the direct button) support pull-up and pulldown resistor circuits; including the internal pull-up resistors in an Arduino. The internal pull-up resistors make it easy to connect a pin to ground through a button or switch. Whether your circuits use pull-up or pulldown resistors is chosen at compile time.

The button list classes enable multiple buttons (of the same type) to be managed together.

### Motivation

The focus of Able is to consume minimal memory for the button capability required. This is important for embedded micro-controllers such as the Arduino Nano with only 32K Flash and 2K SRAM.

## Memory Usage

AbleButtons basic `Buttonable` example consumes 952 bytes of program storage (*only 60 more than Arduino built-in `Button` example*). It also uses 11 bytes for global variables (*only 2 more than `Button`*).

AbleButtons `Debouncable` LED toggle example **only uses 1110 bytes of program storage**, *which is 6 bytes less* than the Arduino's built-in `Debounce` example. It also uses *1 byte less* for global variables. As your program becomes more complex to achieve its purpose, code efficiency will be an advantage with memory constrained devices such as the Arduino Nano with 32K for programs and only 2K for global variables.

The `Buttonable` example is also much easier to read:

```c
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupDirectButton; // Using the direct pull-up button.
using ButtonList = AblePullupDirectButtonList; // Using the direct pull-up button list.

#define BUTTON_PIN 2 // Connect button between this pin and ground.
Button btn(BUTTON_PIN); // The button to check.

void setup() {
  // put your setup code here, to run once:
  
  btn.begin(); // You must always call begin() once for each button.
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  btn.handle(); // You must always call handle() repeatedly in a loop.

  digitalWrite(LED_BUILTIN, btn.isPressed());
}
```

```
Sketch uses 952 bytes (3%) of program storage space. Maximum is 30720 bytes.
Global variables use 11 bytes (0%) of dynamic memory, leaving 2037 bytes for local variables. Maximum is 2048 bytes.
```

Additionally, the `Debouncable` example is also much easier to understand:

```c
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupClickerButton; // Using clicker pull-up button.
using ButtonList = AblePullupClickerButtonList; // Using the clicker pull-up button list.

#define BUTTON_PIN 2 // Connect button between this pin and ground.
Button btn(BUTTON_PIN); // The button to check.

bool led = false; // On/off state of the LED.

void setup() {
  // put your setup code here, to run once:

  btn.begin(); // You must always call begin() once for each button.

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  btn.handle(); // You must always call handle() repeatedly in a loop.

  if(btn.resetClicked()) {
    led = !led;
    digitalWrite(LED_BUILTIN, led);
  }
}
```

## Installation

To manually install this library, download the version you require and extract it into the Arduino libraries directory (normally the libraries sub-folder of the [sketchbook folder](https://support.arduino.cc/hc/en-us/articles/4412950938514) - `$HOME/Documents/Arduino/libraries`)

*NB: The initial version 0.1.0 of this library was called `able-buttons` but was renamed to `AbleButtons` at v0.2.0 due to significant changes in the code.*

Alternatively use the Arduino IDE's library manager to find the `AbleButtons` library. This is the easiest approach.

With either installation approach, your `libraries` directory in your sketchbook folder should contain an `AbleButtons` directory with further files and sub-folders similar to the list below (additional files and directories may be present):

```
/AbleButtons
 |- /docs
 |- /examples
 |   +- /Buttonable
 |   |   `- Buttonable.ino
 |   `- /Debounceable
 |       `- Debouncable.ino
 +- /src
 |   +- AbleButtons.h
 |   +- Button.h
 |   +- ButtonList.h
 |   +- CallbackButton.h
 |   +- ...
 |   `- Pins.h
 +- library.properties
 +- LICENSE
 +- platformio.ini
 `- README.md
```

## Buttons

Different AbleButtons have additional capabilities that build on simpler button features. The following button combinations are available from AbleButtons:

| Using                               | Resistor | Pin    | Callback? | Button List                             |
| :---------------------------------- | :------: | :----: | :-------: | :-------------------------------------- |
| `AblePulldownButton`                | Pulldown | Push   | No        | `AblePulldownButtonList`                |
| `AblePulldownCallbackButton`        | Pulldown | Push   | Yes       | `AblePulldownCallbackButtonList`        |
| `AblePulldownClickerButton`         | Pulldown | Click  | No        | `AblePulldownClickerButtonList`         |
| `AblePulldownCallbackClickerButton` | Pulldown | Click  | Yes       | `AblePulldownCallbackClickerButtonList` |
| `AblePulldownDirectButton`          | Pulldown | Direct | No        | `AblePulldownDirectButtonList`          |
| `AblePullupButton`                  | Pull-up  | Push   | No        | `AblePullupButtonList`                  |
| `AblePullupCallbackButton`          | Pull-up  | Push   | Yes       | `AblePullupCallbackButtonList`          |
| `AblePullupClickerButton`           | Pull-up  | Click  | No        | `AblePullupClickerButtonList`           |
| `AblePullupCallbackClickerButton`   | Pull-up  | Click  | Yes       | `AblePullupCallbackClickerButtonList`   |
| `AblePullupDirectButton`            | Pull-up  | Direct | No        | `AblePullupDirectButtonList`            |

AbleButton classes above identify the features available with them:

* Pulldown and pull-up classes identify which resistor circuit they can be used with.
* `AblePulldownButton` and `AblePullupButton` just provide debounced `isPressed()` detection. This waits until the closed/open state of the button stabalises when the button is pressed or released.
* A "direct" button bypasses the debounce checking. Without debouncing a button, it may appear the button has been pressed and released multiple times due to [contact bouncing](https://en.wikipedia.org/wiki/Switch#Contact_bounce) as the button is pressed or released. If you do not need button debouncing, this can dramatically reduce program size.
* A "clicker" button provides `isClicked()` in addition to `isPressed()` detection. Clicker buttons remember they have been pressed and released to complete a click. Your program can respond when clicked, rather than a simple press.
* A "callback" button provides on-pressed and on-released function callbacks. When the button is pressed and released, a function you define can be called for that event. The callback function receives the `id` of the button pressed or released. This `id` allows a shared callback function to differentiate between those buttons.
* The `AblePulldownCallbackClickerButton` and `AblePullupCallbackClickerButton` classes combine "callback" and "clicker" capabilities if required.

For programs with several buttons, AbleButtons provides a `ButtonList` feature. A program can define a list of buttons and then manage them together. Buttons still work independently (each has its own pressed, clicked and callback settings), but you can call the button list's `begin()` and `handle()` functions to manage all the buttons together.

Remember to choose the appropriate `ButtonList` class for the button you are using:

```c
// Identify which buttons you are using...
using Button = AblePullupClickerButton; // Using clicker pull-up button.
using ButtonList = AblePullupClickerButtonList; // Using the clicker pull-up button list.
```

If you have multiple buttons with different requirements (e.g. a clicker and basic push-button), it is recommended to use a button with the most features for all your buttons. This allows a button list to manage all your buttons together (they must be of the same type) and avoids including duplicate code for both button types. So if you have both push- and clickable-buttons, the following would be the most efficient, since clicker-buttons include push-button capabiities.

```c
using Button = AblePullupClickerButton;
using ButtonList = AblePullupClickerButtonList;
```

## Usage

The full button library documentation can be found [here](https://www.jsware.io/able-buttons/html). The library also provides some examples to help get started with the library.

### Basic Button

Here is a simple button to check if it has been pressed. It can be found in the Buttonable2 example:

```c
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupButton; // AblePullupDirectButton if debouncing not required.
using ButtonList = AblePullupButtonList; // AblePullupDirectButtonList if debouncing not required.

#define BUTTON_PIN 2 // Connect button between this pin and ground.
Button btn(BUTTON_PIN); // The button to check.

void setup() {
  // put your setup code here, to run once:
  
  btn.begin(); // Call the button's begin() method to initialise.

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  btn.handle(); // Call the button's handle() method in a loop.

  if(btn.isPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
```

### Callback Button

Here is an equivalent program using callback functions. It can be found in the ButtonableCallback example:

```c
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupCallbackButton; // Using callback pull-up button.
using ButtonList = AblePullupCallbackButtonList; // Using callback pull-up button list.

// Declarations of callback functions defined later.
void pressedCallback(uint8_t);
void releasedCallback(uint8_t);

#define BUTTON_PIN 2 // Connect button between this pin and ground.
Button btn(BUTTON_PIN, pressedCallback, releasedCallback); // The button to check.

void setup() {
  // put your setup code here, to run once:

  btn.begin();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  btn.handle();
}

void pressedCallback(uint8_t id) {
  digitalWrite(LED_BUILTIN, HIGH);
}

void releasedCallback(uint8_t id) {
    digitalWrite(LED_BUILTIN, LOW);
}
```

## Troubleshooting

AbleButtons is very simple to use. There are just a few things to remember.

1. Remember to choose the button with the resistor circuit and features you are using.
2. Signals from [pulldown](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button) and [pull-up](https://docs.arduino.cc/tutorials/generic/digital-input-pullup) resistors are different. AbleButtons needs to know which one to use. Arduino microcontrollers have internal pull-up resistors, so connecting a pin to ground via a button uses a pull-up resistor circuit.
3. Choose the button features you need from basic button, a clicker and callback functions. If you try to use the clicker-specific methods when `using Button = AbleButton` style commands without "Clicker" in the name will result in compile time errors if you attempt to use any clicker-specific methods (e.g. `isClicked()` and `resetClicked()`).
4. Remember to `begin()` each button in your `setup()` function and `handle()` each button in your `loop()` function. If you are using a `ButtonList`, you can call the `begin()` and `handle()` methods on the list.
5. If using a `ButtonList`, remember to include all your buttons in the list. For this reason it is best (and most memory efficient) to have the same resistor circuit for all your buttons.
6. If you need different features for different buttons, you should be `using Button = AbleButton` with the highest feature set you need over including both feature sets, otherwise duplicate code will be included.

### Resistor Circuits

AbleButton supports both pulldown and pull-up resistor circuits. This affect the pressed vs unpressed signals. With a pulldown resistor, the signal will be "pulled down" to ground when not pressed. When pressed, the button signal will go "high".

With a pull-up resistor (including the internal pull-up resistors), the signal is "pulled high" when not pressed and go low when pressed.

See the [Button](https://docs.arduino.cc/built-in-examples/digital/Button) for a pulldown resistor circuit.

See the [Digital Input Pull-Up Resistor](https://docs.arduino.cc/tutorials/generic/digital-input-pullup) for the internal pull-up resistor circuit. This is much easier as it involves connecting the pin to ground via a button.
