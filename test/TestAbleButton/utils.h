#include <Arduino.h>

#define UNKNOWN_PINMODE 0xFF


template<typename T>
inline Print &operator<<(Print &p, const T o) { p.print(o); return p; }

enum endl { endl };
inline Print &operator <<(Print &p, enum endl) { p.println(); p.flush(); return p; }


extern "C" void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  Serial << F("ERROR: Assertion [ ") << __sexp << F(" ] failed");

  if(__func) {
    Serial << F(" in function '") << __func;
  }

  Serial << F("' at line ") << __lineno ;

  if(__file) {
    Serial << F(" of file ") << __file;
  }

  Serial << endl;
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
