/* RGBDriver
 * Paul Wightmore 2015
 */
#ifndef _RGBDRIVER_h
#define _RGBDRIVER_h

#include "common.h"
#include "IDriver.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class RGBDriver : public IDriver
{
  struct PinDescriptor
  {
    PinDescriptor(uint8_t _rPin, uint8_t _gPin, uint8_t _bPin)
    : rPin(_rPin), gPin(_gPin), bPin(_bPin) {}
    
    uint8_t rPin;
    uint8_t gPin;
    uint8_t bPin;
  }
  RGBDriver(const PinDescriptor& pinDescriptor);
  
  //! Set the overall intensity of all LEDs, relative to their individual intensities
  setIntensity(float intensity);
  //! Set the intensities of the individual LEDs to \p r \p g and \p b
  setRGB(float r, float g, float b);
  //! Set the intensities of the individual LEDs to \p i
  setRGB(float i);
  //! Set the red intensity to \p r
  setRed(float r);
  //! Set the green intensity to \p g
  setGreen(float g);
  //! Set the blue intensity to \p b
  setBlue(float b);
  
  // IDriver implementation
  void reset() override;
};

#endif // _RGBDRIVER_h