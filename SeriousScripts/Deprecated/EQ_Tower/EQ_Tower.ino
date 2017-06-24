/*
  EQ Tower by WhiteLizards

  EQ Tower
*/
// Library für die LED Stripe Programmierung
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
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

// Arrays mit Volumegrenzen für EQ Effekt
int calm[] = {20, 40, 60, 80, 100};
//int loud[] = {80, 150, 200, 280, 300};
int loud[] = {60, 100, 110, 120, 130, 140, 150, 160, 170, 180};
int loud2[] = {160, 200, 250, 300, 350, 400, 450, 500, 550, 600}; //Laptop 2/3 lautstärke
int loud3[] = {160, 210, 270, 330, 380, 440, 490, 550, 610, 660};


void setup() {

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
  Serial.begin(9600);

  Wire.begin();
  Wire.onReceive(receiveEvent);

}

void loop() {
  Read_Frequencies();
  Show_EQ(loud3);
  Print_Frequencies(0);
 
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

void receiveEvent(int arr[7]) {
  Frequencies_One = Wire.read();
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

// Shows the EQ on the LED stripe
void Show_EQ(int arr[]) {
  audioInput = Read_Input(0);

  if (audioInput >= arr[0]) {
    if (audioInput >= arr[1]) {
      if (audioInput >= arr[2]) {
        if (audioInput >= arr[3]) {
          if (audioInput >= arr[4]) {
            if (audioInput >= arr[5]) {
              if (audioInput >= arr[6]) {
                if (audioInput >= arr[7]) {
                  if (audioInput >= arr[8]) {
                    if (audioInput >= arr[9]) {
                      for (int i = 0; i < 50; i++) {
                        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
                      }
                    }
                    else {
                      for (int i = 0; i < 45; i++) {
                        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
                      }
                    }
                  }
                  else {
                    for (int i = 0; i < 40; i++) {
                      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
                    }
                  }
                }
                else {
                  for (int i = 0; i < 35; i++) {
                    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
                  }
                }
              }
              else {
                for (int i = 0; i < 30; i++) {
                  pixels.setPixelColor(i, pixels.Color(0, 255, 0));
                }
              }
            }
            else {
              for (int i = 0; i < 25; i++) {
                pixels.setPixelColor(i, pixels.Color(0, 255, 0));
              }
            }
            
          }
          else {
            for (int i = 0; i < 20; i++) {
              pixels.setPixelColor(i, pixels.Color(0, 255, 0));
            }
          }
          
        }
        else {
          for (int i = 0; i < 15; i++) {
            pixels.setPixelColor(i, pixels.Color(0, 255, 0));
          }
        }
      }
      else {
        for (int i = 0; i < 10; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        }
      }

    }

    else {
      for (int i = 0; i < 5; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      }
    }
  }
  else {
    for (int i = 0; i < 50; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  pixels.show();
}

