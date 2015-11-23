/* IController interface
 * Paul Wightmore 2015
 */
#ifndef _ICONTROLLER_h
#define _ICONTROLLER_h

#include <Arduino.h>

typedef uint8_t pin_t;

class IController
{
public:
  virtual void reset() = 0;
};

#endif // _ICONTROLLER_h