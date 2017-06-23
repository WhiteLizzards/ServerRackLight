/*
  AudioInputTest3 by WhiteLizards

  Lauflicht im LED Schlauch
*/
// Library für die LED Stripe Programmierung
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6
#define NUMPIXELS 9

// Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

#define FILTER_FREQUENCY (222)

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];

int audioInput;

void setup() {

  //Set Spectrum Shield pin configurations
  //pinMode(STROBE, OUTPUT);
  //pinMode(RESET, OUTPUT);
  //pinMode(DC_One, INPUT);
  //pinMode(DC_Two, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  //digitalWrite(STROBE, HIGH);
  //digitalWrite(RESET, HIGH);

  //pixels.begin(); // This initializes the NeoPixel library.

  //Initialize Spectrum Analyzers
  /*
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  */
  Serial.begin(9600);

}

void loop() {
  //Read_Frequencies();

  analogWrite(REDPIN, 200);
  analogWrite(GREENPIN, 200);
  analogWrite(BLUEPIN, 200);
  delay(100);
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  delay(100);
}



// Methods
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

// Returns a specific Frequency
int Read_Input(int i) {
  if (i >= 0 && i < 7) {
    return Frequencies_One[i]; // 0 - 1024
  }
  else {
    return Frequencies_One[0];
  }
}
// Prints out realInput
void Print_Frequencies(int i) {
  audioInput = Read_Input(i);
  Serial.print("Frequency: ");
  Serial.println(audioInput);
}
