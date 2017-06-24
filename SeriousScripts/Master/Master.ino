/*
 * Master by WhiteLizards
 * 
 * Script that handles the audio and poti input and sends them to the slave Arduinos
 * 
 */

#include <Wire.h>

// Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

#define POTIPIN A2
// Declare Frequencies Arrays
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];

// Declare Message variables to send to slaves
String message = "";
int bass = 0;
int snare = 0;
int poti = 0;

// Declare Potentionmeter
int potiPin = A0;

void setup() {
  /*
  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

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
  */
  
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}


void loop() {
  message = CreateMessage();
  //Read_Frequencies();
  SendMessageToDevice(7, message);
  SendMessageToDevice(8, message);
  delay(500); 
}



// Functions
// Creates and return a string message with 3 random numbers
String CreateMessage() {
  bass = random(0, 1024);
  snare = random(0, 1024);
  poti = random(0, 1024);
  return (String)bass + "," + (String)snare + "," +  (String)poti + "C";
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

// Sends a String message to specific device
void SendMessageToDevice(int device, String msg) {
  Wire.beginTransmission(device);
  Wire.print(msg);
  Wire.endTransmission();
}

