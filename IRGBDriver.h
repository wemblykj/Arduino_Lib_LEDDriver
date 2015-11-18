/* IRGBDriver
 * Paul Wightmore 2015
 */
#ifndef _IRGBDRIVER_h
#define _IRGBDRIVER_h

#include "IDriver.h"

class IRGBDriver : public IDriver
{
  struct PinDescriptor
  {
    PinDescriptor(uint8_t _rPin, uint8_t _gPin, uint8_t _bPin)
    : rPin(_rPin), gPin(_gPin), bPin(_bPin) {}
    
    uint8_t rPin;
    uint8_t gPin;
    uint8_t bPin;
  }
  
  //! Get the currently configured pins
  virtual PinDescriptor getPins() = 0
  //! Set the overall intensity of all LEDs, relative to their individual intensities
  virtual setIntensity(float intensity) = 0;
  //! Set the intensities of the individual LEDs to \p r \p g and \p b
  virtual setRGB(float r, float g, float b) = 0;
  //! Set the intensities of the individual LEDs to \p i
  virtual setRGB(float i) = 0;
  //! Set the red intensity to \p r
  virtual setRed(float r) = 0;
  //! Set the green intensity to \p g
  virtual setGreen(float g) = 0;
  //! Set the blue intensity to \p b
  virtual setBlue(float b) = 0;
};

#endif // _IRGBDRIVER_h