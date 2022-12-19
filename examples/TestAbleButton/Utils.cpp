/**
 * @file Utils.cpp TestAbleButton utilities for producing assert failures. This
 * module provides an __assert function implementation for the assert() calls
 * that fail. This function uses locally defined print-stream << operators to
 * make it easier to output to the Serial object using C++ style stream output
 * operations.
 */
#include "TestAbleButton.h"

/**
 * Assert output function. Outputs an assertion failed message to Serial.
 * 
 * @param __func The function name where the assertion failed.
 * @param __file The file name where the assertion failed.
 * @param __lineno The line number in the file where the assertion failed.
 * @param __sexp The assertion expression that evaluated to false.
 */
void __assert(const char *__func, const char *__file, int __lineno, const __FlashStringHelper *__sexp) {
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
