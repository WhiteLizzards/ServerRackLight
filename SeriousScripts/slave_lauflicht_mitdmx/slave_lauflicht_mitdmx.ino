//#include <DmxSimple.h>
#include <FastLED.h>
#include <Wire.h>
const int ledPin =  6;      // the number of the LED pin
const int i2c_adress =  6;      // die i2c Adress
#define NUMPIXELS      MAXPOSITIONS+5      //Anzahl LEDs

//LED-Programm variablen
// Setup the NeoPixel library
int lastState = 0;
int lastState2 = 0;
int pos=0;
#define MAXPOSITIONS 150// eins mehr als gebraucht damit letzte aus geht
int multiplePosition[MAXPOSITIONS];

String command="";
int bass = 0;
int snare = 0;
int potiMapValue = 0;
float potiMapValueFloat = 0;
CRGB leds[NUMPIXELS];

void setup() {
  Serial.begin(9600);
  //DmxSimple.usePin(4);
  FastLED.addLeds<WS2811, ledPin, RGB>(leds, NUMPIXELS );
  Wire.begin(i2c_adress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}
int limit=0;

bool led=false;
  bool triggerd= false;
void loop() {
    Serial.println(bass);
    for ( int i=MAXPOSITIONS-1;i>=0;i--){ //schaue in allen Positionen nach
      
      if (leds[i][0]+leds[i][1]+leds[i][2]>0){
        if (snare>450) { 
          if (i >= MAXPOSITIONS-19) leds[i+1] = CRGB(255,0,0);
          else leds[i+1] = CRGB(0,0,255);  
           //leds[i+1] = CRGB(0,100,255); 
        }
        else {
            
         if (i >= MAXPOSITIONS-19) leds[i+1] = CRGB(255,0,0);
         else leds[i+1] = CRGB(0,0,255); 
        }
        leds[i] = CRGB(0,0,0);
      }
    }
    if (bass>500) {

      leds[0] = CRGB(0,0,255);
      triggerd=false;
    }
    
   FastLED.show();
   delay(18);

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
      if(count==2) potiMapValue = tmp.toInt();
      count++;
      tmp = "";
    }
    else if (command[i] == ',') {
      if (count==0) bass = tmp.toInt();
      else if (count==1) snare = tmp.toInt();
      tmp = "";
      count++;
    }
    else{
      tmp+=(char)command[i];
    }
  }
  command = "";
}

