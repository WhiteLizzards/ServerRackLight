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
int potiMapValue = 0;


// Dev variables
bool usePoti = true;
bool useAudioShield = true;

void setup() {
  if (useAudioShield) {
    //Set Spectrum Shield pin configurations
    pinMode(STROBE, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(DC_One, INPUT);
    pinMode(DC_Two, INPUT);
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
  }
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}


void loop() {
  // Check if we work with dummy or live data
  if (useAudioShield) {
    Read_Frequencies();
    message = CreateLiveMessage();
  }
  else message = CreateDummyMessage();

  // Send Message to slave devices

  SendMessageToDevice(6, message);
  SendMessageToDevice(8, message);
  Serial.println(message);
  delay(50); 
}



// Functions

// Creates and returns a string message with 3 random numbers
String CreateDummyMessage() {
  bass = random(0, 1024);
  snare = random(0, 1024);
  potiMapValue = 2;
  return (String)bass + "," + (String)snare + "," +  (String)potiMapValue + "C";
}

// Creates and returns a string message with live data
String CreateLiveMessage() {
  bass = Frequencies_One[0];
  snare = Frequencies_One[3];
  if (usePoti) {
    poti = analogRead(POTIPIN);
    potiMapValue = map(poti, 0, 1023, 1, 6);
  }
  else potiMapValue = 2;
  
  return (String)bass + "," + (String)snare + "," + (String)potiMapValue + "C";
}

// Reads in the Audio Signals and saves them into Frequencies_One
void Read_Frequencies() {
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

