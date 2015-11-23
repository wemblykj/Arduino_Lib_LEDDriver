/* IRGBController
 * Paul Wightmore 2015
 */
#ifndef _IRGBCONTROLLER_h
#define _IRGBCONTROLLER_h

#include "IController.h"
#include "ILEDIntensity.h"
#include "IRGBIntensity.h"

#include "Common.h"

namespace LEDDriver {

class IRGBController : virtual public IRGBIntensity, virtual public ILEDIntensity, virtual public IController
{
public:
  struct PinDescriptor
  {
    PinDescriptor(pin_t _rPin, pin_t _gPin, pin_t _bPin)
    : rPin(_rPin), gPin(_gPin), bPin(_bPin) {}
    
    pin_t rPin;
    pin_t gPin;
    pin_t bPin;
  };
  
  //! Get the currently configured pins
  virtual struct PinDescriptor getPins() const = 0;
  //! Set the intensities of the individual LEDs to \p r \p g and \p b and the master intensity \p i
  virtual void setRGBI(float r, float g, float b, float i) = 0;
  
};

} // namespace LEDDriver

#endif // _IRGBCONTROLLER_h