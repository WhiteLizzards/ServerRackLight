#include <Adafruit_NeoPixel.h>
#define PIN6 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(49, PIN6, NEO_RGB + NEO_KHZ800); //Maybe try NEO_RGB, coz of color swap

void setup() {
  
  pixels.begin();
  pixels.show(); //Set all Pixels to off
}

void loop() {
  
  for(int i = 0; i < 49; i++){

    pixels.setPixelColor(i, pixels.Color(0,0,150)); //RGBW?

    pixels.show(); //Update the PixelColor

    delay(1000);
    
  }
  for (int j = 49; j > 0; j--) {
    pixels.setPixelColor(j, pixels.Color(0,0,0));

    pixels.show(); //Update the PixelColor
  
    delay(1000);
  }
    

}
