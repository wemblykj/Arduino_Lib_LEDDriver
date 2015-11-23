#include <LEDDriver.h>

const int LED_PIN = 13;

ILEDController* ledController;
float intensity = 0.0f;
float step = 0.1f;

void setup() {
  // Create a new LED controller to drive the LED
  ILEDController* ledController = LEDDriver::createLEDController(LED_PIN, LEDDriver::Low);
}

void loop() {
  if ((intensity <= 0.0f) || (intensity >= 1.0f))
    step = -step;
  
  intensity += step;
  ledController->setIntensity(intensity);
}