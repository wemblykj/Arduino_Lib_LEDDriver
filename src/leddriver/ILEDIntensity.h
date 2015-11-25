/* ILEDIntensity
 * Paul Wightmore 2015
 */
#ifndef _ILEDINTENSITY_h
#define _ILEDINTENSITY_h

namespace LEDDriver {

//! An interface for manipulating the intensity of an LED
class ILEDIntensity
{
public:
  //! Get the overall intensity of the LED
  virtual float getIntensity() const = 0;
  //! Set the overall intensity of the LED
  virtual void setIntensity(float intensity) = 0;
};

} // namespace LEDDriver

#endif // _ILEDINTENSITY_h