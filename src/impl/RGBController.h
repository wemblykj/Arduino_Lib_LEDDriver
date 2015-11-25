/* RGBController
 * Paul Wightmore 2015
 */
#ifndef _RGBCONTROLLER_h
#define _RGBCONTROLLER_h

#include "../IRGBController.h"
#include "ResolutionPolicies.h"

#include "Common.h"

namespace LEDDriver {

//! Policy driven RGBController
/**
 * The software resolution can be higher or lower than the hardware resolution and will be conveted as appropriate. 
 * Higher software resolutions may be useful for retaining precision when mixing RGB intensities with the master 
 * intensity or simply for implementing hardware independent code
 *
 * \tparam T_HardwareBitResolution The bit resolution of the hardware (e.g. 8, 10 or 12 bits)
 * \tparam T_SoftwareBitResolution The bit resolution of the software intensity representation (should be a factor of 2)
 * \tparam T_SoftwareStorageType The storage type of internal software intensities  this must be large enough to 
 *                               accomodate the representation of an intensity of T_SoftwareBitResolution bits)
 * \tparam T_HardwareResolutionPolicy
 * \tparam T_SoftwareResolutionPolicy
 */
template<
  uint8_t T_HardwareBitResolution = 8,
  uint8_t T_SoftwareBitResolution = 8,
  typename T_SoftwareStorageType = uint8_t,
  template <uint8_t, typename> class T_HardwareResolutionPolicy = DefaultHardwareResolutionPolicy,
  template <uint8_t, typename> class T_SoftwareResolutionPolicy = DefaultSoftwareResolutionPolicy
>
class RGBController 
  : public T_HardwareResolutionPolicy<T_HardwareBitResolution, T_SoftwareStorageType>
  , public T_SoftwareResolutionPolicy<T_SoftwareBitResolution, T_SoftwareStorageType>
  , virtual public IRGBController
{ 
protected:
  typedef T_HardwareResolutionPolicy<T_HardwareBitResolution, T_SoftwareStorageType> HardwareResolutionPolicy;
  typedef T_SoftwareResolutionPolicy<T_SoftwareBitResolution, T_SoftwareStorageType> SoftwareResolutionPolicy;
  
public:
  RGBController(const PinDescriptor& pinDescriptor)
    : IRGBController()
    , mMasterIntensity(0)
  {
    mPinData[RED].pin = pinDescriptor.rPin;
    mPinData[GREEN].pin = pinDescriptor.gPin;
    mPinData[BLUE].pin = pinDescriptor.bPin;
  }
  
  virtual ~RGBController() {}
  
  //
  // IRGBController implementation
  
  struct PinDescriptor getPins() const override
  { return PinDescriptor(mPinData[RED].pin, mPinData[GREEN].pin, mPinData[BLUE].pin); }
  
  void setRGBI(float r, float g, float b, float i) override
  {
    setRGBI(SoftwareResolutionPolicy::fromFloat(r), SoftwareResolutionPolicy::fromFloat(g), SoftwareResolutionPolicy::fromFloat(b), SoftwareResolutionPolicy::fromFloat(i));
  }
  
  // IRGBIntensity implementation
  void getRGB(float& r, float& g, float& b) const override
  {
    r = SoftwareResolutionPolicy::toFloat(mPinData[RED].intensity);
    g = SoftwareResolutionPolicy::toFloat(mPinData[GREEN].intensity);
    b = SoftwareResolutionPolicy::toFloat(mPinData[BLUE].intensity);
  }
  
  void setRGB(float r, float g, float b) override
  { setRGB(SoftwareResolutionPolicy::fromFloat(r), SoftwareResolutionPolicy::fromFloat(g), SoftwareResolutionPolicy::fromFloat(b)); }

  void setRGB(float i) override
  {
    const T_SoftwareStorageType ii = SoftwareResolutionPolicy::fromFloat(i);
    setRGBI(ii, ii, ii, mMasterIntensity);
  }
  
  float getRed() const override
  { return SoftwareResolutionPolicy::toFloat(mPinData[RED].intensity); }
  
  void setRed(float r) override
  {
    mPinData[RED].intensity = SoftwareResolutionPolicy::fromFloat(r);
    update();
  }
  
  float getGreen() const override
  { return SoftwareResolutionPolicy::toFloat(mPinData[GREEN].intensity); }
  
  void setGreen(float g) override
  {
    mPinData[GREEN].intensity = SoftwareResolutionPolicy::fromFloat(g);
    update();
  }
  
  float getBlue() const override
  { return SoftwareResolutionPolicy::toFloat(mPinData[BLUE].intensity); }
  
  void setBlue(float b) override
  {
    mPinData[BLUE].intensity = SoftwareResolutionPolicy::fromFloat(b);
    update();
  }
  
  //
  // ILEDIntensity implementation
  float getIntensity() const override
  { return SoftwareResolutionPolicy::toFloat(mMasterIntensity); }

  void setIntensity(float i) override
  {
    mMasterIntensity = SoftwareResolutionPolicy::fromFloat(i);
    update();
  }
 
  //
  // IController implementation
  void reset() override
  {
    setRGBI((T_SoftwareStorageType)0, (T_SoftwareStorageType)0, (T_SoftwareStorageType)0, (T_SoftwareStorageType)0);
  }
  
protected:
  struct PinData {
    PinData() : intensity(0) {}
    pin_t pin;
    T_SoftwareStorageType intensity;
  };
  
  void setRGBI(T_SoftwareStorageType r, T_SoftwareStorageType g, T_SoftwareStorageType b, T_SoftwareStorageType i)
  {
    mPinData[RED].intensity = r;
    mPinData[GREEN].intensity = g;
    mPinData[BLUE].intensity = b;
    mMasterIntensity = i;
    update();
  }
  
  void setRGB(T_SoftwareStorageType r, T_SoftwareStorageType g, T_SoftwareStorageType b)
  {
    setRGBI(r, g, b, mMasterIntensity);
  }
  
  void update()
  {
    updatePin(mPinData[RED]);
    updatePin(mPinData[GREEN]);
    updatePin(mPinData[BLUE]);
  }
  
  void updatePin(const struct PinData& pinData)
  { analogWrite(pinData.pin, HardwareResolutionPolicy::encode(SoftwareResolutionPolicy::normalize(pinData.intensity))); }
  
private:
  enum Pin {
    RED, GREEN, BLUE, NUM_PINS 
  };
  
  PinData mPinData[NUM_PINS];
  T_SoftwareStorageType mMasterIntensity;
};

} // namespace LEDDriver

#endif // _RGBCONTROLLER_h