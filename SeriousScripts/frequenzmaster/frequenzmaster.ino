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

#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>

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
  //Serial.begin(9600);
    pinMode(PIN, OUTPUT);
    Wire.begin(); 
  
}
int limit=0;
void loop() {
  
  bool triggerd= false;
  bool snare = false;
  Read_Frequencies();
  
  if (Frequencies_One[0]>200){

      digitalWrite(PIN, HIGH);

    }
    else digitalWrite(PIN, LOW);
  
  if (Frequencies_One[3]>300)snare =HIGH;

  Serial.println("freq: "+(String)Frequencies_One[3]);
  // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);
  
  
  Serial.println(buttonState2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

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
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(Frequencies_One,4);// sends five bytes
     
}

