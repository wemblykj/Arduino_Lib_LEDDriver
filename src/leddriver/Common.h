/* Common
 * Paul Wightmore 2015
 */
#ifndef _COMMON_h
#define _COMMON_h

#define __ASSERT_USE_STDERR
#include <assert.h>

#include <Arduino.h>

#ifndef nullptr
#define nullptr NULL
#endif

#ifndef static_assert
#define static_assert(x, y)
#endif

namespace LEDDriver {

typedef uint8_t pin_t;

// handle diagnostic informations given by assertion and abort program execution:
// Snippet taken from https://gist.github.com/jlesech/3089916
inline void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link. 
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}

} // namespace LEDDriver

#endif // _COMMON_h
