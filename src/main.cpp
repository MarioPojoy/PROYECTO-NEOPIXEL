#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN       GPIO_NUM_26
#define NUM_LEDS  16
#define WAIT      100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(20);
  strip.show();
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), WAIT);
  colorWipe(strip.Color(0, 255, 0), WAIT);
  colorWipe(strip.Color(0, 0, 255), WAIT);
}