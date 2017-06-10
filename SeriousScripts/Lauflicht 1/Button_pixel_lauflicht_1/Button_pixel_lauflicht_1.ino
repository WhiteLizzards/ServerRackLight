/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;
const int ledPin =  6;      // the number of the LED pin

#define BUTTON_PIN 2
#define BUTTON_PIN2 3

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
#define PIN2            5



// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      100

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;

int lastState = 0;
int lastState2 = 0;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
}

int pos=0;
#define MAXPOSITIONS 101
int multiplePosition[MAXPOSITIONS];

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  
  
  Serial.println(buttonState2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
 

  if (buttonState != lastState){

    lastState = buttonState;
    }
    for ( int i=0;i<MAXPOSITIONS;i++){ //schaue in allen Positionen nach
        
        if (multiplePosition[i]>0){
          
          if (buttonState2 == HIGH) {
             
            pixels.setPixelColor(multiplePosition[i]-1, pixels.Color(0,0,255)); //gib an die aktuelle Position-1 eine Farbe
            //lastState2 = buttonState2;
          }
          else {
             
            pixels.setPixelColor(multiplePosition[i]-1, pixels.Color(0,255,0)); //gib an die aktuelle Position-1 eine Farbe
            //lastState2 = buttonState2;
          }
          
          if (multiplePosition[i]>1) pixels.setPixelColor(multiplePosition[i]-2, pixels.Color(0,0,0)); //stelle die Position -2 auf schwarz, aber nur dann wenn es nicht das erste Pixel ist
          multiplePosition[i] = multiplePosition[i]+1;
          if(multiplePosition[i]>NUMPIXELS+1) multiplePosition[i]=0;
        }
    }
    if (buttonState == HIGH) {
          int fired = 0; // Variable um zu schauen ob schon ausgelöst wurde
          for (int i = 0; i < MAXPOSITIONS; i++) { //alle positionen durchlaufen und eine finden die noch 0 ist und nicht gestartet wurde
            if (multiplePosition[i] == 0) {
              if (fired==0) { //nur dann noch eins auslösen, wennn noch keins ausgelöst wurde
                multiplePosition[i] = multiplePosition[i]+1; //auslösen
                fired = 1; //verhindern das noch eins ausgelöst wurde.
              }
            } 
          }
          
    }
    
    // turn LED off:

    pixels.show();
    delay(40);


}
