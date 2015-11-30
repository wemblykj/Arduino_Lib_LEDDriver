/* ILEDController
 * Paul Wightmore 2015
 */
#ifndef _ILEDCONTROLLER_h
#define _ILEDCONTROLLER_h

#include "leddriver/IController.h"
#include "leddriver/ILEDIntensity.h"

#include "leddriver/Common.h"

namespace LEDDriver {

class ILEDController : virtual public ILEDIntensity, virtual public IController
{
public:
  //! Get the hardware pin of the LED
  virtual pin_t getPin() const = 0;
};

} // namespace LEDDriver

#endif // _ILEDCONTROLLER_h
