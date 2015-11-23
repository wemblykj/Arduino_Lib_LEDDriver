/* ILEDController
 * Paul Wightmore 2015
 */
#ifndef _ILEDCONTROLLER_h
#define _ILEDCONTROLLER_h

#include "IController.h"
#include "ILEDIntensity.h"

class ILEDController : virtual public ILEDIntensity, virtual public IController
{
public:
  //! Get the hardware pin of the LED
  virtual pin_t getPin() const = 0;
};

#endif // _ILEDCONTROLLER_h