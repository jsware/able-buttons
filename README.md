# ABLE

ABLE is a simple, lightweight button library to capture input from buttons connected to an Arduino.

## Introduction

ABLE provides a lightweight easy-to-use button library without unnecessarily including unused button capability. The basic button class uses **194 bytes extra code** to support [button-debouncing](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce) out of the box. This stops isPressed() calls returning a noisy state as a button is pressed or released.

ABLE can support buttons connected using pull-up resitors and pull-down resisters. It also supports the internal pull-up resistors on various Arduino models making it easy to connect a pin to ground through a button or switch.

### Motivation

The focus of ABLE is to consume minimal memory for the button capability required. ABLE provides a suite of button classes for different capabilities over a general purpose button class supporting all types of buttons. You can choose the button capabilities used at compile time, so no redundant code is included. This is important for embedded micro-controllers such as the Arduino Nano with only 32K Flash and 2K SRAM.

If you need more functionality (e.g. callbacks when pressed), ABLE includes a suite of button classes with extended capabilities.

## Memory Usage

The following manual code compiles to 892 bytes using Arduino IDE v1.8.19...

```c
#define BUTTON_PIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
```

```
Sketch uses 892 bytes (2%) of program storage space. Maximum is 30720 bytes.
Global variables use 9 bytes (0%) of dynamic memory, leaving 2039 bytes for local variables. Maximum is 2048 bytes.
```

...with 9 bytes for global variables. **NB: This program's button is not debounced**. Whilst probably not visible with the built-in LED, pressing and releasing the button may register several presses due to the mechanical and physical issues with buttons. 

The same program using the button library **with button debouncing** only uses 1086 bytes (194 bytes more)...

```c
#include <able-buttons.h>

#define BUTTON_PIN 2
BasicButton btn(BUTTON_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  btn.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btn.isPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
```

```
Sketch uses 1140 bytes (3%) of program storage space. Maximum is 30720 bytes.
Global variables use 15 bytes (0%) of dynamic memory, leaving 2033 bytes for local variables. Maximum is 2048 bytes.
```

...with 15 bytes for global variables (6 extra bytes).

## Installation

To manually install this library, download the version you require and extract it into the Arduino libraries directory (normally the libraries sub-folder of the [sketchbook folder](https://support.arduino.cc/hc/en-us/articles/4412950938514) - `$HOME/Documents/Arduino/libraries`)

Alternatively use the Arduino IDE's library manager to find the `able-buttons` library.

With either approach, your `libraries` directory in your sketchbook folder should contain an `able-buttons` directory with further files and sub-folders similar to the list below (additional files and directories may be present):

```
/able-buttons
 |- /docs
 |- /examples
 |   +- /PushBtn
 |   |   `- PushBtn.ino
 |   +- /PushBtnAny
 |   |   `- PushBtnAny.ino
 |   +- /PushBtnAll
 |   |   `- PushBtnAll.ino
 |   `- /PushBtnCallback
 |      `- PushBtnCallback.ino
 +- /src
 |   +- callbtn.h
 |   +- btnlist.h
 |   +- btntypes.h
 |   +- basicbtn.h
 |   `- buttons.h
 +- /tests
 +- .gitignore
 +- Doxyfile
 +- library.properties
 +- LICENSE
 +- platformio.ini
 `- README.md
```

## Usage

The full button library documentation can be found [here](https://www.jsware.io/able-buttons/html). The library provides some examples to help get started with the library.


### Basic Button

Here is a simple button to check if it has been pressed. It can be found in the PushBtn example:

```c
#include <able-buttons.h>

#define BUTTON_PIN 2                        // Macro defining the pin to use.
BasicButton btn(BUTTON_PIN);                // Declare a basic button using the internal pull-up resistor.

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  btn.begin();                              // Call the button's begin() method to initialise.
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btn.isPressed()) {                     // Check if the button is pressed.
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
```

### Callback Button

To see the callback button capability use the PushBtnCallback example:

```c
#include <able-buttons.h>

void pressedCallback(BasicButton *) {       // Callback function for button pressed.
  digitalWrite(LED_BUILTIN, HIGH);
}

void releasedCallback(BasicButton *) {      // Callback function for button released.
    digitalWrite(LED_BUILTIN, LOW);
}

#define BUTTON_PIN 2                        // Connect button between this pin and ground.
CallbackButton btn(BUTTON_PIN, pressedCallback, releasedCallback); // The button to check.

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  btn.begin();                              // Initialise each button using the begin() function.
}

void loop() {
  // put your main code here, to run repeatedly:

  btn.handle();                             // Handle events for the button.
}
```

### Button List

If you have a list of buttons, it's easy to declare them in a list so a single begin() and handle() functions will control them all. The PushBtnAll and PushBtnAny examples show the button list class in action.

```c
#include <able-buttons.h>

#define BUTTON_PIN 2                        // Connect button between this pin and ground.

BasicButton btns[] = {                      // Array of buttons.
  BasicButton(BUTTON_PIN),
  BasicButton(BUTTON_PIN + 1)
};
BasicButtonList btnList(btns);              // List of button to control together.

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  btnList.begin();                          // Call begin on a button list calls begin on all the list's buttons.
}

void loop() {
  // put your main code here, to run repeatedly:

  if(btnList.allPressed()) {                // Check if all the buttons are pressed together.
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
```
