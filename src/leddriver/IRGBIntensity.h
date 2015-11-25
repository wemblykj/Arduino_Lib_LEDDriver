/* IRGBIntensity
 * Paul Wightmore 2015
 */
#ifndef _IRGBINTENSITY_h
#define _IRGBINTENSITY_h

namespace LEDDriver {

//! An interface for manipulating the red, green and blue intensities of an LED
class IRGBIntensity
{
public:
  //! Get the  red, green and blue intensities into \p r \p g and \p b
  virtual void getRGB(float& r, float& g, float& b) const = 0;
  //! Set the red, green and blue intensities to \p r \p g and \p b
  virtual void setRGB(float r, float g, float b) = 0;
  //! Set red, green and blue intensities to \p i
  virtual void setRGB(float i) = 0;
  //! Get the red intensity
  virtual float getRed() const = 0;
  //! Set the red intensity to \p r
  virtual void setRed(float r) = 0;
  //! Get the green intensity
  virtual float getGreen() const = 0;
  //! Set the green intensity to \p g
  virtual void setGreen(float g) = 0;
  //! Get the blue intensity
  virtual float getBlue() const = 0;
  //! Set the blue intensity to \p b
  virtual void setBlue(float b) = 0;
};

} // namespace LEDDriver

#endif // _IRGBINTENSITY_h