#include "leddriver/ILEDController.h"
#include "leddriver/IRGBController.h"

#include "leddriver/Common.h"

namespace LEDDriver {

//! Create an RGB controller with a predefined intensity resolution
/**
 * A custom intensity resolution can be defined by specifying Resolution::Custom and defining CUSTOM_RESOLUTION
 * in your sketch before including the LEDDriver header file.
 *
 * \param pd A descriptor defining the RGB hardware pins
 * \param bits The number of bits used for representing intensity values internally,
 *             this could theoretically be higher or lower than the hardwares capabilities
 * \return An IRGBController instance
 */
IRGBController* createRGBController(const IRGBController::PinDescriptor& pinDescriptor, uint8_t bitResolution = 8);

//! Create a uniform LED controller with a predefined intensity resolution
/**
 * A custom intensity resolution can be defined by specifying Resolution::Custom and defining CUSTOM_RESOLUTION
 * in your sketch before including the LEDDriver header file.
 *
 * \param pin The hardware pin of the LED to drive
 * \param bits The number of bits used for representing intensity values internally, 
          this could theoretically be higher or lower than the hardwares capabilities
 * \return An IRGBController instance
 */
ILEDController* createLEDController(const pin_t& pin, uint8_t bitResolution = 8);

} // namespace LEDDriver
