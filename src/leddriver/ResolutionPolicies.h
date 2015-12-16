/* ResolutionPolicies
 * Paul Wightmore 2015
 */
#ifndef _RESOLUTIONPOLICIES_h
#define _RESOLUTIONPOLICIES_h

#include "leddriver/Common.h"

namespace LEDDriver {

template<
    uint8_t T_SoftwareBitResolution, 
    typename T_SoftwareStorageType 
  >
class DefaultSoftwareResolutionPolicy
{
  // Partial specialization would appear to be a pain in the arse so just use precalculate storate bit resolution using sizeof(T_SoftwareStorageType)
  static const uint8_t storage_bit_resolution = (sizeof(T_SoftwareStorageType)<<3); 

  static_assert((T_SoftwareBitResolution<=16), "T_SoftwareBitResolution must be 16 or less");
  static_assert((T_SoftwareBitResolution<=storage_bit_resolution), "T_SoftwareStorageType must be large enough to represent T_SoftwareBitResolution bits");
  static_assert((T_SoftwareBitResolution%2==0), "T_SoftwareBitResolution must be a factor of 2");
  
protected:
  typedef T_SoftwareStorageType storage_t;
  
  static storage_t fromFloat(float value)
  { return static_cast<storage_t>(value * (float)(1l<<T_SoftwareBitResolution)); }
  
  static float toFloat(storage_t value)
  { return (float)value / (float)(1l<<T_SoftwareBitResolution); }
  
  //! Shift software value so that msb of value is in msb of storage_t
  // Partial specialization would appear to be a pain in the arse so just use sizeof(storage_t), this *should* resolve to a constant value
  storage_t normalize(storage_t value)
  { return value << (storage_bit_resolution-T_SoftwareBitResolution); }
  
};

///////////

template<
    uint8_t T_HardwareBitResolution,
    typename T_SoftwareStorageType
  >
class DefaultHardwareResolutionPolicy
{
  // Partial specialization would appear to be a pain in the arse so just use precalculate storate bit resolution using sizeof(T_SoftwareStorageType)
  static const uint8_t storage_bit_resolution = (sizeof(T_SoftwareStorageType)<<3); 
 
  static_assert((T_HardwareBitResolution == 8 || T_HardwareBitResolution == 10 || T_HardwareBitResolution == 12), "T_HardwareBitResolution must be either 8, 10 or 12"); 
  static_assert((storage_bit_resolution<=16), "T_SoftwareBitResolution must be 16 or less");

protected:
  static uint16_t encode(T_SoftwareStorageType normalizedValue)
  { 
    int rshift = storage_bit_resolution-T_HardwareBitResolution;
    return (rshift<0) ? (normalizedValue<<-rshift) : normalizedValue>>rshift;
  }
};

} // namespace LEDDriver

#endif // _RESOLUTIONPOLICIES_h
