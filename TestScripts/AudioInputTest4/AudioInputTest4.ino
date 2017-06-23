/*
  AudioInputTest3 by WhiteLizards

  Lauflicht im LED Schlauch
*/
// Library für die LED Stripe Programmierung
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 50
#define MAXPOSITIONS 51

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

#define FILTER_FREQUENCY (222)

const int ledPin = 6;
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];

int audioInput;

unsigned long delayval = 100;
unsigned long previousMillis = 0;
unsigned long currentMillis;
boolean triggered = false;
boolean triggeredLast = false;

int minVolume = 100;
int multiplePosition[NUMPIXELS];

void setup() {

  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
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

  for (int i = 0; i < NUMPIXELS; ++i) {
    multiplePosition[i] = 0;
  }

}

void loop() {
  setAll(0,0,0);
  Shoot(0,200,0, 1, 10);

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

// Sets the Pixel of a certain Pixel to a certain Color
void setPixel(int Pixel, int red, int green, int blue) {
   pixels.setPixelColor(Pixel, pixels.Color(red, green, blue));
}

// Sets and shows all Pixel to certain color
void setAll(int red, int green, int blue) {
  for(int i = 0; i < NUMPIXELS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  pixels.show();
}

void Shoot(int red, int green, int blue, int EyeSize, int SpeedDelay) {
  for(int i = 0; i < NUMPIXELS - EyeSize - 2; i++) {
    setAll(0,0,0);
    Read_Frequencies();
  audioInput = Read_Input(0);
    if (audioInput >= minVolume ) {
      for(int j = 1; j <= EyeSize; j++) {
        setPixel(i+j, red, green, blue);
      }
    }
    
    pixels.show();
    delay(40);
  }
}

