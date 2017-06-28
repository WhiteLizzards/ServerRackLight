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
#define PIN2 10
#define NUMPIXELS 50
#define MAXPOSITIONS 51

String command="";
int bass = 0;
int snare = 0;

CRGB pixels[NUMPIXELS];
int mapNum = 0;

// Arrays mit Volumegrenzen für EQ Effekt
/*
int threshold1[] = {80, 100, 120, 140, 160, 200, 240, 250, 300, 300};
int threshold2[] = {120, 150, 180, 240, 280, 320, 350, 420, 450, 450}; //Laptop 2/3 lautstärke
int threshold3[] = {200, 230, 250, 300, 380, 440, 490, 550, 610, 660};
int threshold4[] = {500, 580, 680, 750, 800, 870, 930, 980, 1000, 1000};
*/

// Arrays mit Volumegrenzen für EQ Effekt
int threshold1[] = {80, 140, 200, 250, 300, 350};
int threshold2[] = {120, 150, 240, 320, 350, 450}; //Laptop 2/3 lautstärke
int threshold3[] = {200, 250, 300, 440, 490, 550};
int threshold4[] = {500, 580, 680, 800, 930, 1000};
int threshold5[] = {500, 580, 680, 800, 930, 1000};
int threshold6[] = {500, 580, 680, 800, 930, 1000};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN, OUTPUT);
  FastLED.addLeds<WS2811, PIN, RGB>(pixels, NUMPIXELS);
  FastLED.addLeds<WS2811, PIN2, RGB>(pixels, NUMPIXELS);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  Serial.println(bass);
  Show_EQ(threshold6);
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
  for(int i=0; i<command.length(); i++){
    if (command[i]=='C'){
      if (count==1) snare = tmp.toInt();
      count++;
      tmp = "";
    }
    else if (command[i] == ',') {
      if (count==0) bass = tmp.toInt();
      tmp = "";
      count++;
    }
    else{
      tmp+=(char)command[i];
    }
  }
  command = "";
}

// Shows the EQ on the LED stripe
void Show_EQ(int *arr) {
  if (bass >= arr[0]) {
    if (bass >= arr[1]) {
      if (bass >= arr[2]) {
        if (bass >= arr[3]) {
          if (bass >= arr[4]) {
            if (bass >= arr[5]) {
             for (int i = 0; i < 50; i++) {
                pixels[i].setRGB(200, 0, 0);
              }
            }
            else {
              for (int i = 0; i < 50; i++) {
                pixels[i].setRGB(200, 50, 0);
              }
            }
          }
          else {
            for (int i = 0; i < 40; i++) {
              pixels[i].setRGB(200, 50, 0);
            }
          }
        }
        else {
          for (int i = 0; i < 30; i++) {
            pixels[i].setRGB(200, 50, 0);
          }
        }
      }
      else {
        for (int i = 0; i < 20; i++) {
          pixels[i].setRGB(200, 50, 0);
        }
      }
    }
    else {
      for (int i = 0; i < 10; i++) {
        pixels[i].setRGB(200, 50, 0);
      }
    }
  }
  else {
    for (int i = 0; i < 50; i++) {
      pixels[i].setRGB(0, 0, 0);
    }
  }
}

