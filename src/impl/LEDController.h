/* LEDController
 * Paul Wightmore 2015
 */
#ifndef _LEDCONTROLLER_h
#define _LEDCONTROLLER_h

#include "../ILEDController.h"

template<typename T_StorageType, uint16_t T_IntensityLevels>
class LEDController : virtual public ILEDController
{
public:
  LEDController(const pin_t pin);
  
  virtual ~LEDController() {}
  
  //
  // ILEDController implementation
  
  pin_t getPin() const override;
  
  //
  // ILEDIntensity implementation
  float getIntensity() const override;
  void setIntensity(float intensity) override;
  
  //
  // IController implementation
  void reset() override;
  
protected:
  void setIntensity(T_StorageType i);
  void update();
  
private:
  
  pin_t mPin;
  T_StorageType mIntensity;
};

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
LEDController<T_StorageType, T_IntensityLevels>::LEDController(const pin_t pin)
  : ILEDController()
  , mPin(pin)
  , mIntensity(0)
{
}
  
template<typename T_StorageType, uint16_t T_IntensityLevels> inline
pin_t LEDController<T_StorageType, T_IntensityLevels>::getPin() const
{ 
  return mPin; 
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
float LEDController<T_StorageType, T_IntensityLevels>::getIntensity() const
{
  return (float)mIntensity / (float)T_IntensityLevels;
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void LEDController<T_StorageType, T_IntensityLevels>::setIntensity(float i)
{
  const T_StorageType ii = static_cast<int>(i * T_IntensityLevels);
  mIntensity = ii;
  update();
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void LEDController<T_StorageType, T_IntensityLevels>::reset()
{
  setIntensity((T_StorageType)0);
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void LEDController<T_StorageType, T_IntensityLevels>::update()
{
}

template<typename T_StorageType, uint16_t T_IntensityLevels> inline
void LEDController<T_StorageType, T_IntensityLevels>::setIntensity(T_StorageType i)
{
  mIntensity = i;
  update();
}

#endif // _LEDCONTROLLER_h