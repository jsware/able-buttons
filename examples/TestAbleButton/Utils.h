/**
 * @file Utils.h Utility function declarations.
 * 
 * The Utils module defines general utilities. An assert(bool-expression) that
 * outputs to Serial if its false and print-stream << operators to  make it
 * easier to output to the Serial object using C++ style stream output
 * operations.
 */

#include <Arduino.h>

/**
 * Output assertion to Serial when the assertion expression is false.
 * 
 * @param func The __func__ (function) name.
 * @param file The __FILE__ name.
 * @param lineno The __LINE__ number.
 * @param exp The failing assertion expression.
 */
extern void assertSerial(const char *func, const char *file, int lineno, const __FlashStringHelper *exp);

/**
 * Macro to assert using FlashStringHelper to reduce memory usage. If the
 * boolean expression is false, then an assertion error is output to Serial
 * including the function name, source file, line number and the expression
 * itself.
 * 
 * @param e A boolean expression evaluating to true/false.
 */
#define assert(e) ((e) ? (void)0 : assertSerial(__func__, __FILE__, __LINE__, F(#e)))

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
  endl ///< The special value of endl triggers the Serial.println() and Serial.flush().
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
