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

The **Arduino Button Library Extension** (Able) is a simple, lightweight button library to capture input from buttons connected to an Arduino using minimal memory overhead. For example, the `Buttonable` sample has minimal overhead compared to the equivalent [Button](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button) example included with the Arduino IDE. Additionally, the Able `Debouncable` sample uses *less* program storage than the equivalent [Debounce](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce) program provided with the Arduino IDE.

## Introduction

Able provides a suite of button classes so you can choose the best fit for your needs without including unused capabilities. By choosing, at compile time, the features you require, only the code necessary for those features is included.

For example, if you do not use callback functions, choosing the right button without the callback feature reduces your program's size giving you more space for your project's purpose.

This selection is done with `using Button = AbleButton` and `using ButtonList = AbleButtonList` style commands in your program. You must initialise each button with a `begin()` call in your `setup()` function and `handle()` it in your `loop()` function.

```c++
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

All Able buttons support [button debouncing](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce) (with the exception of the direct button). Button debouncing addresses [contact bounce](https://en.wikipedia.org/wiki/Switch#Contact_bounce) common to mechanical buttons in electronic circuits. Debouncing a button waits for a steady contact so the button does not appear to bounce between open and closed. You can control the debounce wait-time for a steady contact, but the default value is usually sufficient.

All Able buttons (including the direct button) support pull-up and pulldown resistor circuits; including the internal pull-up resistors in an Arduino. The internal pull-up resistors make it easy to connect a pin to ground through a button or switch. Whether your circuits use pull-up or pulldown resistors is chosen at compile time.

The button list classes enable multiple buttons (of the same type) to be managed together.

### Motivation

The focus of Able is to consume minimal memory for the button capability required. This is important for embedded micro-controllers such as the Arduino Nano with only 32K Flash and 2K SRAM.

## Memory Usage

Able's basic `Buttonable` example consumes 952 bytes of program storage (*only 60 more than Arduino built-in `Button` example*). It also uses 11 bytes for global variables (*only 2 more than `Button`*).

Able's `Debouncable` LED toggle example **only uses 1110 bytes of program storage**, *which is 6 bytes less* than the Arduino's built-in `Debounce` example. It also uses *1 byte less* for global variables. As your program becomes more complex to achieve its purpose, code efficiency will be an advantage on memory constrained devices such as the Arduino Nano with 32K for programs and only 2K for global variables.

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

Alternatively use the Arduino IDE's library manager to find the `AbleButtons` library.

With either approach, your `libraries` directory in your sketchbook folder should contain an `AbleButtons` directory with further files and sub-folders similar to the list below (additional files and directories may be present):

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

| Using                             | Resistor | Pin    | Callback? | Button List                           |
| :-------------------------------- | :------: | :----: | :-------: | :------------------------------------ |
| AblePulldownButton                | Pulldown | Push   | No        | AblePulldownButtonList                |
| AblePulldownCallbackButton        | Pulldown | Push   | Yes       | AblePulldownCallbackButtonList        |
| AblePulldownClickerButton         | Pulldown | Click  | No        | AblePulldownClickerButtonList         |
| AblePulldownCallbackClickerButton | Pulldown | Click  | Yes       | AblePulldownCallbackClickerButtonList |
| AblePulldownDirectButton          | Pulldown | Direct | No        | AblePulldownDirectButtonList          |
| AblePullupButton                  | Pull-up  | Push   | No        | AblePullupButtonList                  |
| AblePullupCallbackButton          | Pull-up  | Push   | Yes       | AblePullupCallbackButtonList          |
| AblePullupClickerButton           | Pull-up  | Click  | No        | AblePullupClickerButtonList           |
| AblePullupCallbackClickerButton   | Pull-up  | Click  | Yes       | AblePullupCallbackClickerButtonList   |
| AblePullupDirectButton            | Pull-up  | Direct | No        | AblePullupDirectButtonList            |

AbleButton classes above identify the features available with them:

* Pulldown and pull-up classes identify which resistor circuit they can be used with.
* AblePulldownButton and AblePullupButton provide just debounced isPressed() detection. This waits until the closed/open state of the button stabalises when the button is pressed or released.
* A Direct button bypass debounce checking. Without debouncing a button, it may appear the button has been pressed and released multiple times due to contact bouncing as the button is pressed or released.
* A Clicker button provides isClicked() in addition to isPressed() detection. A "clicker" button remembers it has been pressed and released to complete a click. Your program can respond to a complete click (a press followed by release), rather than a simple press.
* A Callback button provides on-pressed and on-released function calls. When the button is pressed and released, a function you define can be called for that event. The callback function receives the id of the button pressed or released. This allows a common function for multiple buttons to differentiate between those buttons.
* A Callback Clicker button combined Callback and Clicker capabilities.

For programs with several buttons, Able provides a button list feature. A program can define a list of buttons and then manage them together. Buttons still work independently (each has its own pressed, clicked and callback settings), but you can call the button list begin() and handle() functions to manage all the buttons together.

## Usage

The full button library documentation can be found [here](https://www.jsware.io/able-buttons/html). The library also provides some examples to help get started with the library.

### Basic Button

Here is a simple button to check if it has been pressed. It can be found in the PushBtn example:

```c++
#include <AbleButtons.h>

// Identify which buttons you are using...
using Button = AblePullupButton; // AblePullupDirectButton if debouncing not required.
using ButtonList = AblePullupDirectButtonList; // AblePullupDirectButtonList.

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
