/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-neopixel-led-strip
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define PIN_ARR_D 4  
#define PIN_ARR_G 6  
#define NUM_PIXELS 20    // The number of LEDs (pixels) on NeoPixel

#define DELAY_INTERVAL 250  // 250ms pause between each pixel

Adafruit_NeoPixel strip_arr_g(NUM_PIXELS, PIN_ARR_G, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_arr_d(NUM_PIXELS, PIN_ARR_D, NEO_RGBW + NEO_KHZ800);

void setup() {
  strip_arr_g.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip_arr_d.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  strip_arr_g.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  strip_arr_d.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
}

void loop() {
  
  clignot_arr_g();

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_arr_g.numPixels(); i++) {
    strip_arr_g.setPixelColor(i, c);
    strip_arr_g.show();
    delay(wait);
  }
}


void clignot_arr_g() {

  
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    strip_arr_g.setPixelColor(pixel, strip_arr_g.Color(65, 255, 3)); 
    strip_arr_g.show();
    delay(25);      
  }
  delay(500);      
  // strip_arr_g.clear();
  // strip_arr_g.show();
  colorWipe(strip_arr_g.Color(0, 0, 0), 0); // White RGBW
  delay(500);      
}