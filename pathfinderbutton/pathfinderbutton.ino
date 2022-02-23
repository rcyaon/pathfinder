/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D1

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 1200

// constants won't change. They're used here to set pin numbers:
const int buttonGreen = D3;     // the number of the pushbutton pin
const int buttonYellow = D4;
const int buttonRed = D5;
// const int ledPin =  ;      // the number of the LED pin

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// variables will change:
int buttonStateGreen  = 0;         // variable for reading the pushbutton status
int buttonStateYellow = 0;
int buttonStateRed = 0;


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

  // initialize the serial communication:
  Serial.begin(9600);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonGreen, INPUT);
  pinMode (buttonYellow, INPUT);
  pinMode (buttonRed, INPUT);
}


void loop() {
  // read the state of the pushbutton value:
  buttonStateGreen = digitalRead(buttonGreen);
  buttonStateYellow = digitalRead(buttonYellow);
  buttonStateRed = digitalRead(buttonRed);

  Serial.println(buttonStateRed);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateGreen == LOW) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);
      theaterChaseReverse(strip.Color(0,  255 ,   0), 1); // Green, half brightness, 1 microsecond delay
  } 

      if (buttonStateRed == LOW) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);
      theaterChase(strip.Color(255,  0 ,   0), 1); // Red, half brightness, 1 microsecond delay
  } 
  
    if (buttonStateYellow == LOW) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);
      theaterChase(strip.Color(255,  255 ,   0), 1); // Yellow, half brightness, 1 microsecond delay
  } 

}


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip. Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<5; a++) {  // Repeat 100 times...
    for(int b=0; b<5; b++) { //  'b' counts from 0 to 5...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
        for(int c=b; c<strip.numPixels(); c += 5) {
          strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
 strip.clear();         //   Set all pixels in RAM to 0 (off)
 strip.show();
} 


// Theater-marquee-style chasing lights - in reverse.
// Currently unapplicable to the buttons.
void theaterChaseReverse(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 5; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+5) {
        strip.setPixelColor(strip.numPixels() - (i+q), c);    //turn every third pixel on
      }
      
      strip.show();
      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+5) {
        strip.setPixelColor(strip.numPixels() - (i+q), 0);        //turn every third pixel off
      }
    }
     
  }
  strip.clear();         //   Set all pixels in RAM to 0 (off)
     strip.show();
}
