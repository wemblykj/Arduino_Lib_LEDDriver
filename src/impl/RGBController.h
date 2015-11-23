/* RGBController
 * Paul Wightmore 2015
 */
#ifndef _RGBCONTROLLER_h
#define _RGBCONTROLLER_h

#include "../IRGBController.h"

template<typename T_StorageType, uint16_t T_IntensityLevels>
class RGBController : virtual public IRGBController
{
public:
  RGBController(const PinDescriptor& pinDescriptor);
  
  virtual ~RGBController() {}
  
  //
  // IRGBController implementation
  
  struct PinDescriptor getPins() const override;
  void setRGBI(float r, float g, float b, float i) override; 
  
  // IRGBIntensity implementation
  void getRGB(float& r, float& g, float& b) const override;
  void setRGB(float r, float g, float b) override; 
  void setRGB(float i) override;
  float getRed() const override;
  void setRed(float r) override;
  float getGreen() const override;
  void setGreen(float g) override;
  float getBlue() const override;
  void setBlue(float b) override;
  
  //
  // ILEDIntensity implementation
  float getIntensity() const override;
  void setIntensity(float intensity) override;
  
  //
  // IController implementation
  void reset() override;
  
protected:
  void setRGBI(T_StorageType r, T_StorageType g, T_StorageType b, T_StorageType i);
  void setRGB(T_StorageType r, T_StorageType g, T_StorageType b);
  void update();
  
private:
  enum Pin {
    RED, GREEN, BLUE, NUM_PINS 
  };
  
  struct PinData {
    PinData() : intensity(0) {}
    pin_t pin;
    T_StorageType intensity;
  } mPinData[NUM_PINS];
  
  T_StorageType mMasterIntensity;
};

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
RGBController<T_StorageType, T_IntensityLevels>::RGBController(const PinDescriptor& pinDescriptor)
  : IRGBController()
  , mMasterIntensity(0)
{
  mPinData[RED].pin = pinDescriptor.rPin;
  mPinData[GREEN].pin = pinDescriptor.gPin;
  mPinData[BLUE].pin = pinDescriptor.bPin;
}
  
template<typename T_StorageType, uint16_t T_IntensityLevels> inline
struct IRGBController::PinDescriptor RGBController<T_StorageType, T_IntensityLevels>::getPins() const
{ 
  return PinDescriptor(mPinData[RED].pin, mPinData[GREEN].pin, mPinData[BLUE].pin); 
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::getRGB(float& r, float& g, float& b) const
{
  r = (float)mPinData[RED].intensity / (float)T_IntensityLevels;
  g = (float)mPinData[GREEN].intensity / (float)T_IntensityLevels;
  b = (float)mPinData[BLUE].intensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRGBI(float r, float g, float b, float i)
{
  const T_StorageType ri = static_cast<int>((r * (float)T_IntensityLevels));
  const T_StorageType gi = static_cast<int>(g * (float)T_IntensityLevels);
  const T_StorageType bi = static_cast<int>(b * (float)T_IntensityLevels);
  const T_StorageType ii = static_cast<int>(i * (float)T_IntensityLevels);
  setRGBI(ri, gi, bi, ii);
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRGB(float r, float g, float b)
{
  const T_StorageType ri = static_cast<int>(r * T_IntensityLevels);
  const T_StorageType gi = static_cast<int>(g * T_IntensityLevels);
  const T_StorageType bi = static_cast<int>(b * T_IntensityLevels);
  setRGB(ri, gi, bi);
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRGB(float i)
{
  const T_StorageType ii = static_cast<int>(i * (float)T_IntensityLevels);
  setRGBI(ii, ii, ii, mMasterIntensity);
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
float RGBController<T_StorageType, T_IntensityLevels>::getRed() const
{
  return (float)mPinData[RED].intensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRed(float r)
{
  const T_StorageType ri = static_cast<int>(r * T_IntensityLevels);
  mPinData[RED].intensity = ri;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
float RGBController<T_StorageType, T_IntensityLevels>::getGreen() const
{
  return (float)mPinData[GREEN].intensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setGreen(float g)
{
  const T_StorageType gi = static_cast<int>(g * T_IntensityLevels);
  mPinData[GREEN].intensity = gi;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
float RGBController<T_StorageType, T_IntensityLevels>::getBlue() const
{
  return (float)mPinData[BLUE].intensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setBlue(float b)
{
  const T_StorageType bi = static_cast<int>(b * T_IntensityLevels);
  mPinData[BLUE].intensity = bi;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
float RGBController<T_StorageType, T_IntensityLevels>::getIntensity() const
{
  return (float)mMasterIntensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setIntensity(float i)
{
  const T_StorageType ii = static_cast<int>(i * T_IntensityLevels);
  mMasterIntensity = ii;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::reset()
{
  setRGBI((T_StorageType)0, (T_StorageType)0, (T_StorageType)0, (T_StorageType)0);
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::update()
{
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRGBI(T_StorageType r, T_StorageType g, T_StorageType b, T_StorageType i)
{
  mPinData[RED].intensity = r;
  mPinData[GREEN].intensity = g;
  mPinData[BLUE].intensity = b;
  mMasterIntensity = i;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void RGBController<T_StorageType, T_IntensityLevels>::setRGB(T_StorageType r, T_StorageType g, T_StorageType b)
{
  setRGBI(r, g, b, mMasterIntensity);
}

#endif // _RGBCONTROLLER_h