#include "LEDDriver.h"

#include "LEDController.h"
#include "RGBController.h"

#include "Arduino.h"

namespace LEDDriver {

IRGBController* createRGBController(const IRGBController::PinDescriptor& pd, const Resolution& res)
{
  switch (res) {
    case Low:
      return new RGBController<uint8_t, Low>(pd);
      break;
    case Medium:
      return new RGBController<uint16_t, Medium>(pd);
      break;
    case High:
      return new RGBController<uint16_t, High>(pd);
      break;
    case Custom:
      static_assert((Custom <= 65536), "custom resolution must be 65536 or less");
      if (Custom <= 256)
        return new RGBController<uint8_t, Custom>(pd);
      else
        return new RGBController<uint16_t, Custom>(pd);
      break;
  }
  
  return nullptr;
}

ILEDController* createLEDController(const pin_t& pin, const Resolution& res)
{
  switch (res) {
    case Low:
      return new LEDController<uint8_t, Low>(pin);
      break;
    case Medium:
      return new LEDController<uint16_t, Medium>(pin);
      break;
    case High:
      return new LEDController<uint16_t, High>(pin);
      break;
    case Custom:
      static_assert((Custom <= 65536), "custom resolution must be 65536 or less");
      if (Custom <= 256)
        return new LEDController<uint8_t, Custom>(pin);
      else
        return new LEDController<uint16_t, Custom>(pin);
      break;
  }
  
  return nullptr;
}

} // namespace LEDDriver