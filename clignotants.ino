/**************************************************************************
 * I N C L U D E S 
**************************************************************************/
#include <Adafruit_NeoPixel.h>

/**************************************************************************
 * G L O B A L   V A R S 
**************************************************************************/

// STRIP PINOUT
const byte PIN_RIGHT = 20; 
const byte PIN_FRONT = 19;  
const byte PIN_LEFT =  18;  

// BUTTONS PINOUT
const byte PIN_AVA_BUT =  9;  
const byte PIN_WRN_BUT =  5; 
const byte PIN_ARR_BUT =  3; 
const byte PIN_GAU_BUT =  7;  
const byte PIN_DRO_BUT =  8;  
const byte PIN_GAY_BUT =  6;  
const byte PIN_RED_BUT = 16;  


const byte PIN_LED_R = 13;  
const byte PIN_LED_L = 4;  
const byte PIN_RELAY = 15;  

const byte NUM_PIX_FRONT =  40;
const byte NUM_PIX_BACK  =  20;

const byte  SHORT_DELAY = 10;
const byte  LONG_DELAY = 250;

Adafruit_NeoPixel strip_left(NUM_PIX_BACK, PIN_LEFT, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_right(NUM_PIX_BACK, PIN_RIGHT, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip_front(NUM_PIX_FRONT,PIN_FRONT, NEO_RGBW + NEO_KHZ800);

volatile byte buttonState = 0;
volatile byte status_front_light = 0;
volatile byte status_back_light = 0;
volatile byte status_left_light = 0;
volatile byte status_right_light = 0;
volatile byte status_warn_light = 0;
volatile byte status_gay_light = 0;

/**************************************************************************
 * S E T U P
**************************************************************************/
void setup() {

  //Serial.begin(9600);

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

  attachInterrupt(PIN_WRN_BUT, irq_warn, FALLING);
  attachInterrupt(PIN_GAU_BUT, irq_left, FALLING);
  attachInterrupt(PIN_DRO_BUT, irq_right, FALLING);
  attachInterrupt(PIN_GAY_BUT, irq_gay, FALLING);

  strip_front.begin();
  strip_left.begin();
  strip_right.begin();

  clear_them_all();
}

/**************************************************************************
 *  C L E A R 
**************************************************************************/
void clear_them_all() {
  buttonState = 0;
  status_left_light = 0;
  status_right_light = 0;
  status_warn_light = 0;
  status_gay_light = 0;
  status_gay_light = 0;
  status_front_light = 0;
  status_back_light = 0;
 
  strip_front.clear();
  strip_left.clear();
  strip_right.clear();
}

/**************************************************************************
 * L O O P
**************************************************************************/
void loop() {
  // F R O N T 
  buttonState = digitalRead(PIN_AVA_BUT);
  if (buttonState == LOW) {

    if (status_front_light) {
      //Serial.println("FRONT PRESSED: OFF ! ");
      status_front_light = false;
      front_light(status_front_light);
    } else {
      //Serial.println("FRONT PRESSED: ON ! ");
      status_front_light = true;
      front_light(status_front_light);
    }
  }
  // B A C K 
  buttonState = digitalRead(PIN_ARR_BUT);
  if (buttonState == LOW) {
    if (status_back_light) {
      //Serial.println("BACK PRESSED: OFF ! ");
      status_back_light = false;
      back_light(status_back_light);
    } else {
      //Serial.println("BACK PRESSED: ON ! ");
      status_back_light = true;
      back_light(status_back_light);
    }

  }

  // R E D
  buttonState = digitalRead(PIN_RED_BUT);
  if (buttonState == LOW) {
    //Serial.println("RED PRESSED ! ");
    cop_flash(strip_front.Color(0, 255,0), 1);
    cop_flash(strip_front.Color(0, 0,0), 1);
    cop_flash(strip_front.Color(0, 0, 255), 1);
    cop_flash(strip_front.Color(0, 0,0), 1);
    cop_flash(strip_front.Color(0, 255,0), 1);
    cop_flash(strip_front.Color(0, 0,0), 1);
    cop_flash(strip_front.Color(0, 0, 255), 1);
    strip_front.clear();
    strip_left.clear();
    strip_right.clear();
    strip_front.fill(strip_front.Color(0, 0, 0, 0));
    strip_left.fill(strip_front.Color(0, 0, 0, 0));
    strip_right.fill(strip_front.Color(0, 0, 0, 0));
    strip_front.show();
    strip_left.show();
    strip_right.show();
  }

  if (status_warn_light) {
    clignot_warn();
    delay(LONG_DELAY);      
  }

  if (status_right_light) {
    clignot_right();
    delay(LONG_DELAY);      
  }

  if (status_left_light) {
    clignot_left();
    delay(LONG_DELAY);      
  }
  delay(100);
}
/**************************************************************************
 * W A R N  I S R 
**************************************************************************/
void irq_warn() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > LONG_DELAY)
  {
    if (status_warn_light) {
     clear_them_all(); 
    } else {
     status_warn_light = true; 
    }
  }
}
/**************************************************************************
 * L E F T   I S R 
**************************************************************************/
void irq_left() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > LONG_DELAY)
  {
    if (status_left_light) {
     clear_them_all(); 
    } else {
     status_left_light = true; 
    }
  }
}
/**************************************************************************
 * L E F T   I S R 
**************************************************************************/
void irq_right() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > LONG_DELAY)
  {
    if (status_right_light) {
     clear_them_all(); 
    } else {
     status_right_light = true; 
    }
  }
}
/**************************************************************************
 * G A Y  I S R 
**************************************************************************/
void irq_gay() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > LONG_DELAY)
  {
    status_gay_light = !status_gay_light;
    if (status_gay_light) {
      gay_parade();
    } else {
      clear_them_all;
    }
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
 * C O P   F L A S H 
**************************************************************************/
void cop_flash(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip_front.clear();         //   Set all pixels in RAM to 0 (off)
      strip_left.clear();         //   Set all pixels in RAM to 0 (off)
      strip_right.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip_front.numPixels(); c += 3) {
        strip_front.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip_left.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip_right.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip_front.show(); // Update strip with new contents
      strip_right.show(); // Update strip with new contents
      strip_left.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
/**************************************************************************
 * W H E E L   O F   C O L O R S 
**************************************************************************/
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip_front.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_front.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip_front.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/**************************************************************************
 * G A Y   P A R A D E
**************************************************************************/
void gay_parade() {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i< strip_front.numPixels(); i++) {
      strip_front.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    for(i=0; i< strip_left.numPixels(); i++) {
      strip_left.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    for(i=0; i< strip_right.numPixels(); i++) {
      strip_right.setPixelColor(i, Wheel((i*1+j) & 255));
    }

    strip_front.show();
    strip_left.show();
    strip_right.show();
    if  (!status_gay_light) {
      clear_them_all();
      strip_right.fill(strip_front.Color(0, 0, 0, 0));
      strip_right.show();
      strip_front.clear();
      return;
    }
    delay(SHORT_DELAY);
  }

}
/**************************************************************************
 * B A C K   L I G H T
**************************************************************************/
void back_light(bool enabled ) {
  if (enabled) {
    
    for(int j=0; j<256; j++) { // Ramp up from 0 to 255
      strip_right.fill(strip_right.Color(0, 254, 0, strip_right.gamma8(j)));
      strip_right.show();
      strip_left.fill(strip_left.Color(0, 254, 0, strip_left.gamma8(j)));
      strip_left.show();
    }

  } else {

    for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
      strip_right.fill(strip_right.Color(0, 254, 0, strip_right.gamma8(j)));
      strip_right.show();
      strip_left.fill(strip_left.Color(0, 254, 0, strip_left.gamma8(j)));
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

