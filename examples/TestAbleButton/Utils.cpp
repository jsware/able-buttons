/**
 * @file Utils.cpp TestAbleButton utilities for producing assert failures. This
 * module provides an __assert function implementation for the assert() calls
 * that fail. This function uses locally defined print-stream << operators to
 * make it easier to output to the Serial object using C++ style stream output
 * operations.
 */
#include "Utils.h"

//
// Implementation of assertSerial...
//
void assertSerial(const char *func, const char *file, int lineno, const __FlashStringHelper *exp) {
  Serial << F("ERROR: Assertion [ ") << exp << F(" ] failed");

  if(func) {
    Serial << F(" in function '") << func;
  }

  Serial << F("' at line ") << lineno;

  if(file) {
    Serial << F(" of file ") << file;
  }

  Serial << endl;
}
