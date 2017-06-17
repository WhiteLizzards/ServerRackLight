/*
  AudioInputTest by WhiteLizards

  Erstes Script, welches die LEDs auf ein Audio Signal regieren lässt
*/
// Library für die LED Stripe Programmierung
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 

const int ledPin = 6;

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];

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

}

void loop() {
  Read_Frequencies();
  
  if (Frequencies_One[0] >=400){
    for (int i = 0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(252,0,15));
        //pixels.setPixelColor(i, pixels.Color((int)random(0,100),(int)random(0,20),(int)random(0,100)));
    }
  }
  
  else {
    for (int i = 0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
  }
  pixels.show();

  
  



  //Serial.println(Frequencies_One[0]);
  Serial.println(Frequencies_One[1]);
  //Serial.println(Frequencies_One[2]);
  //Serial.println(Frequencies_One[3]);
  //Serial.println(Frequencies_One[4]);
  //Serial.println(Frequencies_One[5]);
  //Serial.println(Frequencies_One[6]);
  //Graph_Frequencies();
  

}

void Read_Frequencies() {
  // Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++) {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

void Graph_Frequencies(){
   for( int i= 0; i<7; i++)
   {
     if(Frequencies_Two[i] > Frequencies_One[i]){
      
     }
     else{
     }
   }
}




