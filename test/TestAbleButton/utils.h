#include <Arduino.h>

#define UNKNOWN_PINMODE 0xFF

extern "C" void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  Serial.print(F("ERROR: Assertion [ "));
  Serial.print(__sexp);
  Serial.print(F(" ] failed"));
  if(__func) {
    Serial.print(F(" in function '"));
    Serial.print(__func);
  }

  Serial.print(F("' at line "));
  Serial.print(__lineno);
  
  // if(__file) {
  //   Serial.print(F(" of file "));
  //   Serial.print(__file);
  // }
  Serial.println();
  Serial.flush();
}



int8_t getPinMode(uint8_t pin)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);

  // I don't see an option for mega to return this, but whatever...
  if (NOT_A_PIN == port) return UNKNOWN_PINMODE;

  // Is there a bit we can check?
  if (0 == bit) return UNKNOWN_PINMODE;

  // Is there only a single bit set?
  if (bit & (bit - 1)) return UNKNOWN_PINMODE;

  volatile uint8_t *reg, *out;
  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if (*reg & bit)
    return OUTPUT;
  else if (*out & bit)
    return INPUT_PULLUP;
  else
    return INPUT;
}
