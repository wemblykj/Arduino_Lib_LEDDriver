#include <LEDDriver.h>

const int R_PIN = 5;
const int G_PIN = 6;
const int B_PIN = 9;

IRGBController* rgbController;
int colour = 1;
float intensity = 0.0f;
float step = 0.1f;

void setup() {
  // Define the hardware pins for driving R, G and B
  IRGBController::PinDescriptor pd(R_PIN, G_PIN, B_PIN);
  // Create a new RGB controller
  IRGBController* rgbController = LEDDriver::createRGBController(pd, LEDDriver::Low);
}

void loop() {
  if (intensity <= 0.0f)
  {
    step = -step;
    // iterate through a simple 'zx spectrum' style palette
    const float i = (colour & 8) ? 1.0f : 0.85f;  // intensity bit
    const float r = i * float(colour & 2);
    const float g = i * float(colour & 4);
    const float b = i * float(colour & 1);
  
    rgbController->setRGB(r, g, b);
    colour = constrain(colour+1, 1, 15);
  }
  else if (intensity >= 1.0f)
    step = -step;
  
  intensity += step;
  rgbController->setIntensity(intensity);
}