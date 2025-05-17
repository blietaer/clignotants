/**************************************************************************
 * I N C L U D E S 
**************************************************************************/
#include <Adafruit_NeoPixel.h>

/**************************************************************************
 * G L O B A L   V A R S 
**************************************************************************/

// STRIP PINOUT
#define PIN_ARR_D 4  
#define PIN_FRONT 7  
#define PIN_ARR_G 6  

// BUTTONS PINOUT
#define PIN_AVA_BUT 9  
#define PIN_ARR_BUT 12  
#define PIN_GAU_BUT 13  
#define PIN_DRO_BUT 14  
#define PIN_WRN_BUT 10  
#define PIN_GAY_BUT 18  
#define PIN_RED_BUT 19  


#define NUM_PIX_FRONT 40
#define NUM_PIX_BACK  20

#define SHORT_DELAY 10
#define LONG_DELAY 250

Adafruit_NeoPixel strip_arr_g(NUM_PIX_BACK, PIN_ARR_G, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_arr_d(NUM_PIX_BACK, PIN_ARR_D, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_front(NUM_PIX_FRONT,PIN_FRONT, NEO_RGBW + NEO_KHZ800);

int buttonState = 0;

/**************************************************************************
 * S E T U P
**************************************************************************/
void setup() {

  Serial.begin(9600);

  pinMode(PIN_AVA_BUT, INPUT_PULLUP);
  pinMode(PIN_ARR_BUT, INPUT_PULLUP);
  pinMode(PIN_GAU_BUT, INPUT_PULLUP);
  pinMode(PIN_DRO_BUT, INPUT_PULLUP);
  pinMode(PIN_WRN_BUT, INPUT_PULLUP);
  pinMode(PIN_GAY_BUT, INPUT_PULLUP);
  pinMode(PIN_RED_BUT, INPUT_PULLUP);

  strip_front.begin();
  strip_arr_g.begin();
  strip_arr_d.begin();

  strip_front.clear();
  strip_arr_g.clear();
  strip_arr_d.clear();
}

/**************************************************************************
 * L O O P
**************************************************************************/
void loop() {

  // Serial.println("Loop... ");
  buttonState = digitalRead(PIN_AVA_BUT);
  if (buttonState == LOW) {
    Serial.println("FRONT PRESSED ! ");
    clignot_arr_d();
  }
  buttonState = digitalRead(PIN_ARR_BUT);
  if (buttonState == LOW) {
    Serial.println("BACK PRESSED ! ");
    clignot_arr_d();
  }
  buttonState = digitalRead(PIN_GAU_BUT);
  if (buttonState == LOW) {
    Serial.println("LEFT PRESSED ! ");
    clignot_arr_g();
  }
  buttonState = digitalRead(PIN_DRO_BUT);
  if (buttonState == LOW) {
    Serial.println("RIGHT PRESSED ! ");
    clignot_arr_d();
  }
  buttonState = digitalRead(PIN_WRN_BUT);
  if (buttonState == LOW) {
    Serial.println("WARN PRESSED ! ");
    clignot_arr_d();
  }
  buttonState = digitalRead(PIN_GAY_BUT);
  if (buttonState == LOW) {
    Serial.println("GAY PRESSED ! ");
    clignot_arr_d();
  }
  buttonState = digitalRead(PIN_RED_BUT);
  if (buttonState == LOW) {
    Serial.println("RED PRESSED ! ");
    clignot_arr_d();
  }

  delay(100);
}
/**************************************************************************
 * W I P E    F R O N T
**************************************************************************/
void colorWipe_f(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_arr_g.numPixels(); i++) {
    strip_front.setPixelColor(i, c);
    strip_front.show();
    delay(wait);
  }
}

/**************************************************************************
 * W I P E    B A C K - R I G H T
**************************************************************************/
void colorWipe_d(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_arr_g.numPixels(); i++) {
    strip_arr_d.setPixelColor(i, c);
    strip_arr_d.show();
    delay(wait);
  }
}

/**************************************************************************
 * W I P E    B A C K - L E F T
**************************************************************************/
void colorWipe_g(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_arr_g.numPixels(); i++) {
    strip_arr_g.setPixelColor(i, c);
    strip_arr_g.show();
    delay(wait);
  }
}
/**************************************************************************
 * B L I N K    B A C K - R I G H T
**************************************************************************/
void clignot_arr_d() {
  for (int pixel = 0; pixel < NUM_PIX_BACK; pixel++) {
    strip_arr_d.setPixelColor(pixel, strip_arr_d.Color(65, 255, 3)); 
    strip_arr_d.show();
    delay(SHORT_DELAY);      
  }
  delay(LONG_DELAY);      
  colorWipe_d(strip_arr_d.Color(0, 0, 0), 0); // White RGBW
}
/**************************************************************************
 * B L I N K    B A C K - L E F T
**************************************************************************/
void clignot_arr_g() {
  for (int pixel = 0; pixel < NUM_PIX_BACK; pixel++) {
    strip_arr_g.setPixelColor(pixel, strip_arr_g.Color(65, 255, 3)); 
    strip_arr_g.show();
    delay(SHORT_DELAY);      
  }
  delay(LONG_DELAY);      
  colorWipe_g(strip_arr_g.Color(0, 0, 0), 0); // White RGBW
}


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip_front.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip_front.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip_front.numPixels(); c += 3) {
        strip_front.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip_front.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}


void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if(whiteLength >= strip_front.numPixels()) whiteLength = strip_front.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for(;;) { // Repeat forever (or until a 'break' or 'return')
    for(int i=0; i<strip_front.numPixels(); i++) {  // For each pixel in strip_front...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip_front.setPixelColor(i, strip_front.Color(0, 0, 0, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip_front.numPixels());
        // strip_front.setPixelColor(i, strip_front.gamma8(strip_front.ColorHSV(pixelHue)));
      }
    }

    strip_front.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= strip_front.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= strip_front.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}

void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip_front.fill(strip_front.Color(0, 0, 0, strip_front.gamma8(j)));
    strip_front.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip_front.fill(strip_front.Color(0, 0, 0, strip_front.gamma8(j)));
    strip_front.show();
    delay(wait);
  }
}

