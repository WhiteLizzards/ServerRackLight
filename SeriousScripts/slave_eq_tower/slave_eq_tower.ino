/**
 * Slave_EQ_Tower by WhiteLizards
 * 
 * Script for slave EQ Tower
 * 
 */

#include <Wire.h>
#include <FastLED.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 50
#define MAXPOSITIONS 51

String command="";
int bass, snare, potiBass, potiSnare;

CRGB pixels[NUMPIXELS];
int mapNum = 0;

// Arrays mit Volumegrenzen für EQ Effekt
int calm[] = {20, 40, 60, 80, 100};
//int loud[] = {80, 150, 200, 280, 300};
int loud[] = {60, 100, 110, 120, 130, 140, 150, 160, 170, 180};
int loud2[] = {160, 200, 250, 300, 350, 400, 450, 500, 550, 600}; //Laptop 2/3 lautstärke
int loud3[] = {160, 210, 270, 330, 380, 440, 490, 550, 610, 660};
int loud4[] = {200, 260, 320, 380, 440, 500, 560, 620, 680, 740};


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN, OUTPUT);
  FastLED.addLeds<WS2811, PIN, RGB>(pixels, NUMPIXELS);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  Serial.println(bass);
  
  Show_EQ(loud4);
  FastLED.show();
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
    if (command[i]=='C'){
      if(count==0)bass=tmp.toInt();
      else if(count==1)snare=tmp.toInt();
      count++;
      tmp="";
    }
    else{
      tmp+=(char)command[i];
    }
  }
  command="";
}

// Shows the EQ on the LED stripe
void Show_EQ(int arr[]) {
  //mapNum = map(random(0,1024), 0, 1024, 0, 10);
  /*
  switch (mapNum) {
    case 0:
      for (int i = 0; i < 50; i++) {
        pixels[i].setRGB(0, 0, 0);
      }
      break;
    case 1:
      for (int i = 0; i < 5; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 2:
      for (int i = 0; i < 10; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 3:
      for (int i = 0; i < 15; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 4:
      for (int i = 0; i < 20; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 5:
      for (int i = 0; i < 25; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 6:
      for (int i = 0; i < 30; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 7:
      for (int i = 0; i < 35; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 8:
      for (int i = 0; i < 40; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 9:
      for (int i = 0; i < 45; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    case 10:
      for (int i = 0; i < 50; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
      break;
    default:
      for (int i = 0; i < 50; i++) {
        pixels[i].setRGB(0, 0, 0);
      }
      break;
  }
  */
  
  if (bass >= arr[0]) {
    if (bass >= arr[1]) {
      if (bass >= arr[2]) {
        if (bass >= arr[3]) {
          if (bass >= arr[4]) {
            if (bass >= arr[5]) {
              if (bass >= arr[6]) {
                if (bass >= arr[7]) {
                  if (bass >= arr[8]) {
                    if (bass >= arr[9]) {
                      for (int i = 0; i < 50; i++) {
                        pixels[i].setRGB(0, 200, 0);
                      }
                    }
                    else {
                      for (int i = 0; i < 45; i++) {
                        pixels[i].setRGB(0, 200, 0);
                      }
                    }
                  }
                  else {
                    for (int i = 0; i < 40; i++) {
                      pixels[i].setRGB(0, 200, 0);
                    }
                  }
                }
                else {
                  for (int i = 0; i < 35; i++) {
                    pixels[i].setRGB(0, 200, 0);
                  }
                }
              }
              else {
                for (int i = 0; i < 30; i++) {
                  pixels[i].setRGB(0, 200, 0);
                }
              }
            }
            else {
              for (int i = 0; i < 25; i++) {
                pixels[i].setRGB(0, 200, 0);
              }
            }
            
          }
          else {
            for (int i = 0; i < 20; i++) {
              pixels[i].setRGB(0, 200, 0);
            }
          }
          
        }
        else {
          for (int i = 0; i < 15; i++) {
            pixels[i].setRGB(0, 200, 0);
          }
        }
      }
      else {
        for (int i = 0; i < 10; i++) {
          pixels[i].setRGB(0, 200, 0);
        }
      }

    }

    else {
      for (int i = 0; i < 5; i++) {
        pixels[i].setRGB(0, 200, 0);
      }
    }
  }
  else {
    for (int i = 0; i < 50; i++) {
      pixels[i].setRGB(0, 0, 0);
    }
  }
  
}

