#include "ILEDController.h"
#include "IRGBController.h"

// Set default custom resolution, can be overridden by sketch
#ifndef CUSTOM_RESOLUTION
#define CUSTOM_RESOLUTION 512
#endif

namespace LEDDriver {

//! Available intensity resolution for a controller
/**
  * Resolution defines the number of discrete steps available for controlling an LED's intensity
  */
enum Resolution {
  Low = 256,
  Medium = 1024,
  High = 4096,
  Custom = CUSTOM_RESOLUTION
};

//! Create an RGB controller with a predefined intensity resolution
/**
 * A custom intensity resolution can be defined by specifying Resolution::Custom and defining CUSTOM_RESOLUTION
 * in your sketch before including the LEDDriver header file.
 *
 * \param pd A descriptor defining the RGB hardware pins
 * \param res The intensity resolution to use for the controller
 * \return An IRGBController instance
 */
IRGBController* createRGBController(const IRGBController::PinDescriptor& pinDescriptor, const Resolution& resolution = Medium);

//! Create a uniform LED controller with a predefined intensity resolution
/**
 * A custom intensity resolution can be defined by specifying Resolution::Custom and defining CUSTOM_RESOLUTION
 * in your sketch before including the LEDDriver header file.
 *
 * \param pin The hardware pin of the LED to drive
 * \param res The intensity resolution to use for the controller
 * \return An IRGBController instance
 */
ILEDController* createLEDController(const pin_t& pin, const Resolution& resolution = Medium);

} // namespace LEDDriver