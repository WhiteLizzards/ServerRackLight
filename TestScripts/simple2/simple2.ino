// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      100 

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long delayval = 50;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long currentMillis;
int i = 0;
boolean done = false;

void setup() {
  
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  Serial.begin(9600);
  
}

void loop() {

  currentMillis = millis();
  Serial.println(i);

    if (!done) {
      if ((currentMillis - previousMillis) >= delayval) {
        previousMillis = currentMillis;
        
        pixels.setPixelColor(i, pixels.Color(random(0,50),random(0,100),random(0,200)));
        if (i!=0) pixels.setPixelColor(i-1, pixels.Color(0,0,0));
        pixels.show(); 
  
        i++; 
        }
        if (i == NUMPIXELS) {
          done = true;
        }
    }
    else {
      if ((currentMillis - previousMillis) >= delayval)  {
        previousMillis = currentMillis;
  
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        if (i!=0) pixels.setPixelColor(i-1, pixels.Color(random(0,50),random(0,100),random(0,200)));
    
        pixels.show(); 
  
        i--;
        }
        if (i == 0) {
          done = false;
        }
    }
    

    
    
    
    
  
}
