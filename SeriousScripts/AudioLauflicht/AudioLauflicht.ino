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

// Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];


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
int pos=0;
#define MAXPOSITIONS 101 // eins mehr als gebraucht damit letzte aus geht
int multiplePosition[MAXPOSITIONS];

void setup() {

  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}
int limit=0;
void loop() {
  
  bool triggerd= false;
  bool snare = false;
  Read_Frequencies();
  
  if (Frequencies_One[0]>200){
    if (limit>4){
      triggerd =HIGH;
      limit=0;
      }
    else limit++;
    }
  
  if (Frequencies_One[3]>300)snare =HIGH;

  Serial.println("freq: "+(String)Frequencies_One[0]);
  // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);
  
  
  //Serial.println(buttonState2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
 

  if (triggerd != lastState){

    lastState = triggerd;
    }
    for ( int i=0;i<MAXPOSITIONS;i++){ //schaue in allen Positionen nach
        
        if (multiplePosition[i]>0){
          
          if (snare == HIGH) {
             
            pixels.setPixelColor(multiplePosition[i]-1, pixels.Color(255,255,255)); //gib an die aktuelle Position-1 eine Farbe
            //lastState2 = buttonState2;
          }
          else {
             
            pixels.setPixelColor(multiplePosition[i]-1, pixels.Color(0,0,255)); //gib an die aktuelle Position-1 eine Farbe
            //lastState2 = buttonState2;
          }
          
          if (multiplePosition[i]>1) pixels.setPixelColor(multiplePosition[i]-2, pixels.Color(0,0,0)); //stelle die Position -2 auf schwarz, aber nur dann wenn es nicht das erste Pixel ist
          multiplePosition[i] = multiplePosition[i]+1;
          if(multiplePosition[i]>NUMPIXELS+1) multiplePosition[i]=0;
        }
    }
    if (triggerd == HIGH) {
          int fired = 0; // Variable um zu schauen ob schon ausgelöst wurde
          for (int i = 0; i < MAXPOSITIONS; i++) { //alle positionen durchlaufen und eine finden die noch 0 ist und nicht gestartet wurde
            if (multiplePosition[i] == 0) {
              if (fired==0) { //nur dann noch eins auslösen, wennn noch keins ausgelöst wurde
                multiplePosition[i] = multiplePosition[i]+1; // 0 ist ruhezustand, ab 1 läuft es hoch
                fired = 1; //verhindern das noch eins ausgelöst wurde.
              }
            } 
          }
          
    }
    
    // turn LED off:

    pixels.show();
    delay(50);


}

// Reads in the Audio Signals and saves them into Frequencies_One
void Read_Frequencies() {
  // Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++) {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
  
}
