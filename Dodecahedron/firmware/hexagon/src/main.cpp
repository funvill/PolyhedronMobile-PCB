#include <Arduino.h>
#include "FastLED.h"
const int PIN_LED_STATUS = 13;   // IO-13 or pin 16
const int PIN_LED = D4 ; // 14;           // IO-14 or pin 13
const uint32_t BAUD_RATE = 115200;

// The build version is shown on the loading screen.
// the version is shown in the serial prompt and the web page.
const uint8_t BUILD_NUMBER = 1;

const uint16_t PIXELS_COUNT = 266;
CRGB leds[PIXELS_COUNT];

#define BRIGHTNESS          32

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void flipTheStatusLED()
{
  static bool statusLEDState = LOW;
  statusLEDState = !statusLEDState;
  digitalWrite(PIN_LED_STATUS, statusLEDState);
}

void setup() {
  // Set the status led to an output
  // This shows that there is power to the boards
  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_LED_STATUS, HIGH);

  // Set up the serial port for debugging
  // this prevents the button_next, and button_prev from working
  Serial.begin(BAUD_RATE);

  // Print a message to the serial port
  Serial.println("Test Using Pin 8 v" + String(BUILD_NUMBER));

  // Configure the LEDs
  FastLED.addLeds<NEOPIXEL, PIN_LED>(leds, PIXELS_COUNT);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  
  // Flash the status LED
  EVERY_N_SECONDS(1)
  {
    Serial.println("Flip " + String(millis()));
    flipTheStatusLED(); 
  }

  // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 10 ) { gHue ++; } 

  // FastLED's built-in rainbow generator
  fill_rainbow( leds, PIXELS_COUNT, gHue, 7);

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
}
