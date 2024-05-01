#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN           GPIO_NUM_26
#define NUM_LEDS      16
#define WAIT          100
#define WAIT_RAINBOW  20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

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
  colorWipe(strip.Color(0, 0, 0), WAIT);
  colorWipe(strip.Color(255, 0, 0), WAIT);
  colorWipe(strip.Color(0, 255, 0), WAIT);
  colorWipe(strip.Color(0, 0, 255), WAIT);
  colorWipe(strip.Color(0, 0, 0), WAIT);
  rainbow(WAIT_RAINBOW);
}