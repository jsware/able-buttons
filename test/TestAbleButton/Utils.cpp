/**
 * @file Utils.cpp TestAbleButton utilities for producing assert failures. This
 * module provides an __assert function implementation for the assert() calls
 * that fail. This function uses locally defined print-stream << operators to
 * make it easier to output to the Serial object using C++ style stream output
 * operations.
 */
#include <Arduino.h>

/**
 * Output a specific type to the Print stream.
 * 
 * @param p The print-stream to output to.
 * @param o The object to output.
 * 
 * @returns The print-stream object (allows chaining of << operators - as in
 *          `Serial << x << y << z;`).
 */
template<typename T>
inline Print &operator<<(Print &p, const T o) { p.print(o); return p; }

/// Special type to allow `Serial << endl` to print a line and flush the stream.
enum endl {
  endl ///< The special value of endl  triggers the Serial.println() and Serial.flush().
};

/**
 * Special stream operator for turning Serial << endl into new line and stream flush.
 * 
 * @param p The print-stream to output a new line and flush.
 * @param endl The special `endl` enumeration type
 * 
 * @returns The print-stream object (allows chaining of << operators - as in
 *          `Serial << x << y << z;`).
 */
inline Print &operator <<(Print &p, enum endl) { p.println(); p.flush(); return p; }

/**
 * Assert output function. Outputs an assertion failed message to Serial.
 * 
 * @param __func The function name where the assertion failed.
 * @param __file The file name where the assertion failed.
 * @param __lineno The line number in the file where the assertion failed.
 * @param __sexp The assertion expression that evaluated to false.
 */
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
