/* ILEDIntensity
 * Paul Wightmore 2015
 */
#ifndef _ILEDINTENSITY_h
#define _ILEDINTENSITY_h

//! An interface for manipulating the intensity of an LED
class ILEDIntensity
{
public:
  //! Get the overall intensity of the LED
  virtual float getIntensity() const = 0;
  //! Set the overall intensity of the LED
  virtual void setIntensity(float intensity) = 0;
};

#endif // _ILEDINTENSITY_h