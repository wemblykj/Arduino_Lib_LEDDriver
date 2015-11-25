/* LEDController
 * Paul Wightmore 2015
 */
#ifndef _LEDCONTROLLER_h
#define _LEDCONTROLLER_h

#include "../ILEDController.h"
#include "ResolutionPolicies.h"

#include "Common.h"

namespace LEDDriver {

//! Policy driven LEDController
/**
 * The software resolution can be higher or lower than the hardware resolution and will be conveted as appropriate. 
 * Using different resolutions may be useful for implementing hardware independent code
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
class LEDController 
  : public T_HardwareResolutionPolicy<T_HardwareBitResolution, T_SoftwareStorageType>
  , public T_SoftwareResolutionPolicy<T_SoftwareBitResolution, T_SoftwareStorageType>
  , virtual public ILEDController
{
protected:
  typedef T_HardwareResolutionPolicy<T_HardwareBitResolution, T_SoftwareStorageType> HardwareResolutionPolicy;
  typedef T_SoftwareResolutionPolicy<T_SoftwareBitResolution, T_SoftwareStorageType> SoftwareResolutionPolicy;
  
public:
  LEDController(const pin_t pin)
    : ILEDController()
    , mPin(pin)
    , mIntensity(0)
  {
  }
  
  virtual ~LEDController() {}
  
  //
  // ILEDController implementation
  
  pin_t getPin() const override
  { return mPin; }
  
  //
  // ILEDIntensity implementation
  float getIntensity() const override
  { return SoftwareResolutionPolicy::toFloat(mIntensity); }
  
  void setIntensity(float i) override
  { setIntensity(SoftwareResolutionPolicy::fromFloat(i)); }
  
  //
  // IController implementation
  void reset() override
  { setIntensity((T_SoftwareStorageType)0); }
  
protected:
  void setIntensity(T_SoftwareStorageType i)
  { 
    mIntensity = i;
    update();
  }
  
  void update()
  { analogWrite(mPin, HardwareResolutionPolicy::encode(SoftwareResolutionPolicy::normalize(mIntensity))); }
  
private:
  
  pin_t mPin;
  T_SoftwareStorageType mIntensity;
};

} // namespace LEDDriver

#endif // _LEDCONTROLLER_h