#include <Arduino.h>

const uint32_t APPLICATION_SERIAL_BAUD_RATE = 115200;

#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 7
CRGB leds[NUM_LEDS];
void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(APPLICATION_SERIAL_BAUD_RATE);
}
void loop()
{
  leds[0] = CRGB::White;
  FastLED.show();
  delay(30);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(30);

  Serial.println("marker");
}