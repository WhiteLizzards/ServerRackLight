/**
 * Slave_EQ_Tower by WhiteLizards
 * 
 * Script for slave EQ Tower
 * 
 */


#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 50
#define MAXPOSITIONS 51

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String command="";
int bass, snare, potiBass, potiSnare;

// Arrays mit Volumegrenzen für EQ Effekt
int calm[] = {20, 40, 60, 80, 100};
//int loud[] = {80, 150, 200, 280, 300};
int loud[] = {60, 100, 110, 120, 130, 140, 150, 160, 170, 180};
int loud2[] = {160, 200, 250, 300, 350, 400, 450, 500, 550, 600}; //Laptop 2/3 lautstärke
int loud3[] = {160, 210, 270, 330, 380, 440, 490, 550, 610, 660};


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN, OUTPUT);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  if (bass >= potiBass) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
  
  delay(100);
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
  int count=0;
void receiveEvent(int howMany) {
  count=0;
  while (0 < Wire.available()) {
   // loop through all but the last
    command+=(char)Wire.read(); // receive byte as a character       // print the character
  }
  String tmp="";

  for(int i=0; i<command.length();i++){
    if (command[i]==','||command[i]=='C'){
      if(count==0)bass=tmp.toInt();
      else if(count==1)snare=tmp.toInt();
      else if(count==2)potiBass=tmp.toInt();
      else if(count==3)potiSnare=tmp.toInt();
      count++;
      tmp="";
    }
    else{
      tmp+=(char)command[i];
    }
  }
  //Serial.println(command);
  Serial.println("bass:" + (String) bass);
  //Serial.println("snare:" + (String) snare);
  //Serial.println("potiBass:" + (String) potiBass);
  //Serial.println("potiSnare:" + (String) potiSnare);
  
  command="";
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

