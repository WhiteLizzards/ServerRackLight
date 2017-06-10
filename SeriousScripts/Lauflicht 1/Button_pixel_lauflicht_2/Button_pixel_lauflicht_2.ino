/*
  Button_pixel_lauflicht_2 by WhiteLizzards

  Button 1: Lauflicht
  Button 2: Farbe ändern
  Poti 1: BPM/Geschwindigkeit des Lauflichts ändern
 */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Konstanten
const int buttonPin = 2;    
const int buttonPin2 = 3;
const int ledPin =  6;

#define BUTTON_PIN 2
#define BUTTON_PIN2 3
#define PIN         6
#define PIN2        5
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      100

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);


// Variablen
#define MAXPOSITIONS 101
int buttonState = 0;
int buttonState2 = 0;     
int lastState = 0;
int lastState2 = 0;
int pos = 0;
int delayTime = 1;
int newDelayTime = delayTime;
int analogValue = 0;
float voltage = 0;

int multiplePosition[MAXPOSITIONS];

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  analogValue = analogRead(A0);
  voltage = (analogValue * (10.0/1023.0))*10;
  newDelayTime = delayTime*voltage;
  Serial.println(newDelayTime);
  
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
    delay(newDelayTime);


}
