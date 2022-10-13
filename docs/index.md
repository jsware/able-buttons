---
title: Arduino Button Library Extension (ABLE)
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
# Arduino Button Library Extension (ABLE)

ABLE is a simple, lightweight button library to capture input from buttons connected to an Arduino.

## Introduction

ABLE provides a lightweight easy-to-use button library without unnecessarily including unused button capability. The basic button class uses **52 bytes extra code** over the same functionality without.

ABLE can support buttons connected using pull-up resitors and pull-down resisters. It also supports the internal pull-up resistors on various Arduino models making it easy to connect a pin to ground through a button or switch.

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

...with 9 bytes for global variables. The same program using the button library only uses 944 bytes (52 bytes more)...

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
Sketch uses 944 bytes (3%) of program storage space. Maximum is 30720 bytes.
Global variables use 10 bytes (0%) of dynamic memory, leaving 2038 bytes for local variables. Maximum is 2048 bytes.
```

...with 10 bytes for global variables (1 extra byte).

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
