/**************************************************************************
 * I N C L U D E S 
**************************************************************************/
#include <Adafruit_NeoPixel.h>

/**************************************************************************
 * G L O B A L   V A R S 
**************************************************************************/

// STRIP PINOUT
#define PIN_RIGHT 4  
#define PIN_FRONT 7  
#define PIN_LEFT 6  

// BUTTONS PINOUT
#define PIN_AVA_BUT 9  
#define PIN_WRN_BUT 10  
#define PIN_ARR_BUT 12  
#define PIN_GAU_BUT 13  
#define PIN_DRO_BUT 14  
#define PIN_GAY_BUT 18  
#define PIN_RED_BUT 19  


#define PIN_LED_R 15  
#define PIN_LED_L 16  
#define PIN_RELAY 17  


#define NUM_PIX_FRONT 40
#define NUM_PIX_BACK  20

#define SHORT_DELAY 10
#define LONG_DELAY 250

Adafruit_NeoPixel strip_left(NUM_PIX_BACK, PIN_LEFT, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_right(NUM_PIX_BACK, PIN_RIGHT, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_front(NUM_PIX_FRONT,PIN_FRONT, NEO_RGBW + NEO_KHZ800);

int buttonState = 0;
int status_front_light = 0;
int status_back_light = 0;
int status_left_light = 0;
int status_right_light = 0;
int status_warn_light = 0;

/**************************************************************************
 * S E T U P
**************************************************************************/
void setup() {

  Serial.begin(9600);

  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_L, OUTPUT);
  
  pinMode(PIN_AVA_BUT, INPUT_PULLUP);
  pinMode(PIN_ARR_BUT, INPUT_PULLUP);
  pinMode(PIN_GAU_BUT, INPUT_PULLUP);
  pinMode(PIN_DRO_BUT, INPUT_PULLUP);
  pinMode(PIN_WRN_BUT, INPUT_PULLUP);
  pinMode(PIN_GAY_BUT, INPUT_PULLUP);
  pinMode(PIN_RED_BUT, INPUT_PULLUP);

  strip_front.begin();
  strip_left.begin();
  strip_right.begin();

  strip_front.clear();
  strip_left.clear();
  strip_right.clear();
}

/**************************************************************************
 * L O O P
**************************************************************************/
void loop() {

  if (status_left_light) {
    // clignot_left();
    Serial.println("LEFT IS STILL ON ! ");
    delay(LONG_DELAY);      
  }

  if (status_right_light) {
    // clignot_right();
    Serial.println("RIGHT IS STILL ON ! ");
    delay(LONG_DELAY);      
  }

  // F R O N T 
  buttonState = digitalRead(PIN_AVA_BUT);
  if (buttonState == LOW) {

    if (status_front_light) {
      Serial.println("FRONT PRESSED: OFF ! ");
      status_front_light = false;
      front_light(status_front_light);
    } else {
      Serial.println("FRONT PRESSED: ON ! ");
      status_front_light = true;
      front_light(status_front_light);
    }
  }
  
  // B A C K 
  buttonState = digitalRead(PIN_ARR_BUT);
  if (buttonState == LOW) {
    if (status_back_light) {
      Serial.println("BACK PRESSED: OFF ! ");
      status_back_light = false;
      back_light(status_back_light);
    } else {
      Serial.println("BACK PRESSED: ON ! ");
      status_back_light = true;
      back_light(status_back_light);
    }

  }

  // L E F T 
  buttonState = digitalRead(PIN_GAU_BUT);
  if (buttonState == LOW) {
    if (status_left_light) {
      Serial.println("LEFT PRESSED: OFF ! ");
      status_left_light = false;
    } else {
      Serial.println("LEFT PRESSED: ON ! ");
      status_left_light = true;
    }

  }

  // R I G H T
  buttonState = digitalRead(PIN_DRO_BUT);
  if (buttonState == LOW) {
    if (status_right_light) {
    Serial.println("RIGHT PRESSED: OFF ! ");
      status_right_light = false;
    } else {
    Serial.println("RIGHT PRESSED: ON ! ");
      status_right_light = true;
    }
  }

  // W A R N 
  buttonState = digitalRead(PIN_WRN_BUT);
  if (buttonState == LOW) {
    Serial.println("WARN PRESSED ! ");
    clignot_warn();
  }

  // G A Y 
  buttonState = digitalRead(PIN_GAY_BUT);
  if (buttonState == LOW) {
    Serial.println("GAY PRESSED ! ");
    clignot_right();
  }

  // R E D
  buttonState = digitalRead(PIN_RED_BUT);
  if (buttonState == LOW) {
    Serial.println("RED PRESSED ! ");
    theaterChase(strip_front.Color(0, 255,0), 2);
    theaterChase(strip_front.Color(0, 0, 255), 2);
    theaterChase(strip_front.Color(0, 255,0), 2);
    theaterChase(strip_front.Color(0, 0, 255), 2);
  }

}
/**************************************************************************
 * B L I N K    R I G H T
**************************************************************************/
void clignot_right() {
  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_LED_R, HIGH);
  for (int pixel = 0; pixel < NUM_PIX_BACK; pixel++) {
    strip_right.setPixelColor(pixel, strip_right.Color(65, 255, 3)); 
    strip_right.show();
    int pixel_f = NUM_PIX_BACK - pixel;
    strip_front.setPixelColor(pixel_f, strip_front.Color(65, 255, 3)); 
    strip_front.show();
    delay(SHORT_DELAY);      
  }
  delay(LONG_DELAY);      
  strip_right.fill(strip_front.Color(0, 0, 0, 0));
  strip_right.show();
  strip_front.fill(strip_front.Color(0, 0, 0, 0));
  strip_front.show();
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED_R, LOW);
}
/**************************************************************************
 * B L I N K    L E F T
**************************************************************************/
void clignot_left() {
  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_LED_L, HIGH);
  for (int pixel = 0; pixel < NUM_PIX_BACK; pixel++) {
    strip_left.setPixelColor(pixel, strip_left.Color(65, 255, 3)); 
    strip_left.show();
    int pixel_f = NUM_PIX_BACK + pixel;
    strip_front.setPixelColor(pixel_f, strip_front.Color(65, 255, 3)); 
    strip_front.show();
    delay(SHORT_DELAY);      
  }
  delay(LONG_DELAY);      
  strip_left.fill(strip_front.Color(0, 0, 0, 0));
  strip_left.show();
  strip_front.fill(strip_front.Color(0, 0, 0, 0));
  strip_front.show();

  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED_L, LOW);
}
/**************************************************************************
 * B L I N K    W A R N
**************************************************************************/
void clignot_warn() {
  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_LED_L, HIGH);
  digitalWrite(PIN_LED_R, HIGH);
  for (int pixel = 0; pixel < NUM_PIX_BACK; pixel++) {
    strip_left.setPixelColor(pixel, strip_left.Color(65, 255, 3)); 
    strip_left.show();
    int pixel_fl = NUM_PIX_BACK + pixel;
    strip_front.setPixelColor(pixel_fl, strip_front.Color(65, 255, 3)); 
    strip_front.show();
    strip_right.setPixelColor(pixel, strip_right.Color(65, 255, 3)); 
    strip_right.show();
    int pixel_fr = NUM_PIX_BACK - pixel;
    strip_front.setPixelColor(pixel_fr, strip_front.Color(65, 255, 3)); 
    strip_front.show();

    delay(SHORT_DELAY);      
  }
  delay(LONG_DELAY);      
  strip_left.fill(strip_front.Color(0, 0, 0, 0));
  strip_left.show();
  strip_front.fill(strip_front.Color(0, 0, 0, 0));
  strip_front.show();
  strip_right.fill(strip_front.Color(0, 0, 0, 0));
  strip_right.show();
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED_L, LOW);
  digitalWrite(PIN_LED_R, LOW);
}

/**************************************************************************
 * T H E A T R E   C H A S E 
**************************************************************************/
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

/**************************************************************************
 * W H I T E   O V E R   R A I N B O W
**************************************************************************/
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
/**************************************************************************
 * B A C K   L I G H T
**************************************************************************/
void back_light(bool enabled ) {
  if (enabled) {
    
    for(int j=0; j<256; j++) { // Ramp up from 0 to 255
      strip_right.fill(strip_right.Color(0, 255, 0, strip_right.gamma8(j)));
      strip_right.show();
      strip_left.fill(strip_left.Color(0, 255, 0, strip_left.gamma8(j)));
      strip_left.show();
    }

  } else {

    for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
      strip_right.fill(strip_right.Color(0, 255, 0, strip_right.gamma8(j)));
      strip_right.show();
      strip_left.fill(strip_left.Color(0, 255, 0, strip_left.gamma8(j)));
      strip_left.show();
    }
  }
}

/**************************************************************************
 * F R O N T  L I G H T
**************************************************************************/
void front_light(bool enabled ) {
  if (enabled) {
    for(int j=0; j<256; j++) { // Ramp up from 0 to 255
      strip_front.fill(strip_front.Color(0, 0, 0, strip_front.gamma8(j)));
      strip_front.show();
    }
  } else {

    for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
      strip_front.fill(strip_front.Color(0, 0, 0, strip_front.gamma8(j)));
      strip_front.show();
    }
  }
}

