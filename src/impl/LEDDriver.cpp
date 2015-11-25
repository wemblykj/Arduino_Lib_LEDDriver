#include "..\LEDDriver.h"

#include "LEDController.h"
#include "RGBController.h"

#include "..\leddriver\ResolutionPolicies.h"

#include "..\leddriver\Common.h"

namespace LEDDriver {

#define CREATE_CONTROLLER_CASE(controllerType, hardwareRes, controllerRes, controllerStorageType, controllerArg) \
    case controllerRes: \
      return new controllerType\
        <\
          hardwareRes, controllerRes, controllerStorageType,\
          DefaultHardwareResolutionPolicy,\
          DefaultSoftwareResolutionPolicy\
        >(controllerArg);
        
IRGBController* createRGBController(const IRGBController::PinDescriptor& pd, uint8_t bitRes)
{
  assert((bitRes <= 16) && "resolution must be 16 bits or less");
  
  // TODO: Determine hardware resolution from architecture and allocated pin numbers
  static const uint8_t hardware_res = 8;

  // TODO: Refactor common functionality into template class if possible
  switch (bitRes) {
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 2, uint8_t, pd)
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 4, uint8_t, pd)
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 8, uint8_t, pd)
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 10, uint16_t, pd)
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 12, uint16_t, pd)
    CREATE_CONTROLLER_CASE(RGBController, hardware_res, 16, uint16_t, pd)
    default:
      assert(! "resolution must be either 2, 4, 8, 10, 12 or 16 bits");
      break;
  };
  
  return nullptr;
}

ILEDController* createLEDController(const pin_t& pin, uint8_t bitRes)
{
  assert((bitRes <= 12) && "resolution must be 12 bits or less");
  
  // TODO: Determine hardware resolution from architecture and allocated pin numbers
  static const uint8_t hardware_res = 8;
  
  switch (bitRes) {
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 2, uint8_t, pin)
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 4, uint8_t, pin)
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 8, uint8_t, pin)
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 10, uint16_t, pin)
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 12, uint16_t, pin)
    CREATE_CONTROLLER_CASE(LEDController, hardware_res, 16, uint16_t, pin)
    default:
      assert(! "resolution must be either 2, 4, 8, 10, 12 or 16 bits");
      break;
  }
  
  return nullptr;
}

} // namespace LEDDriver
