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
int bass, snare;
int count=0;
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

    for ( int i=MAXPOSITIONS-1;i>=0;i--){ //schaue in allen Positionen nach
      if (leds[i][0]+leds[i][1]+leds[i][2]>0){
        if (snare>450) {  
           leds[i+1] = CRGB(20,100,255); 
        }
        else {  
         leds[i+1] = CRGB(0,0,255); 
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
void receiveEvent() {
  count=0;
  while (0 < Wire.available()) {
   // loop through all but the last
    command+=(char)Wire.read(); // receive byte as a character       // print the character
  }
  String tmp="";

  for(int i=0; i<command.length();i++){
    if (command[i]=='C'){
      if(count==1)snare=tmp.toInt();

      tmp="";

    }
    else if (command[i]==','){
      if(count==0)bass=tmp.toInt();
      tmp="";
      count++;
      
    }
    else{
      tmp+=(char)command[i];
    }
  }
  Serial.println("bass:" + (String) bass);
  command="";

}

