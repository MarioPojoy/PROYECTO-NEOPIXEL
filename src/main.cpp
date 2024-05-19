#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#if defined(ARDUINO_UNOR4_MINIMA)
  #define PIN           PIN_D2
#elif defined(ARDUINO_D1_UNO32)
  #define PIN           GPIO_NUM_26
#elif defined(ARDUINO_AVR_UNO)
  #define PIN           2
#endif

#define NUM_LEDS      16          //  Numero de leds del anillo
#define WAIT          75          //  Delay de barrido de leds
#define WAIT_RAINBOW  10          //  Delay de efecto arcoiris

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//Funcion helper para efecto arcoiris
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

//Efecto arcoiris
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

//Efecto barrido Leds
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
  colorWipe(strip.Color(255, 0, 0), WAIT);  // Rojo
  colorWipe(strip.Color(0, 255, 0), WAIT);  // Verde
  colorWipe(strip.Color(0, 0, 255), WAIT);  // Azul

  colorWipe(strip.Color(255, 255, 0), WAIT);  // Amarillo
  colorWipe(strip.Color(255, 0, 255), WAIT);  // Morado
  colorWipe(strip.Color(0, 255, 255), WAIT);  // Turquesa

  colorWipe(strip.Color(0, 0, 0), WAIT);
  rainbow(WAIT_RAINBOW);
}