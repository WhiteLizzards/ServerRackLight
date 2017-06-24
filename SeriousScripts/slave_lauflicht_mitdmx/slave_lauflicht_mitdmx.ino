//#include <DmxSimple.h>
#include <FastLED.h>
#include <Wire.h>
const int ledPin =  6;      // the number of the LED pin
const int i2c_adress =  8;      // die i2c Adress
#define NUMPIXELS      100      //Anzahl LEDs

//LED-Programm variablen
// Setup the NeoPixel library
int lastState = 0;
int lastState2 = 0;
int pos=0;
#define MAXPOSITIONS NUMPIXELS+1// eins mehr als gebraucht damit letzte aus geht
int multiplePosition[MAXPOSITIONS];

String command="";
int bass, snare;
int count=0;
CRGB leds[NUMPIXELS];

void setup() {
  Serial.begin(115200);
  //DmxSimple.usePin(4);
  FastLED.addLeds<WS2811, ledPin, RGB>(leds, NUMPIXELS );
  Wire.begin(i2c_adress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}
int limit=0;

bool led=false;
  bool triggerd= false;
void loop() {


    for ( int i=0;i<MAXPOSITIONS;i++){ //schaue in allen Positionen nach
        
        if (multiplePosition[i]>0){
          
          if (snare == HIGH) {  
               leds[multiplePosition[i]-1] = CRGB(255,255,255); 

          }
          else {  
           leds[multiplePosition[i]-1] = CRGB(0,0,255); 
          }
          if (multiplePosition[i]>1)leds[multiplePosition[i]-2] = CRGB(0,0,0);  //stelle die Position -2 auf schwarz, aber nur dann wenn es nicht das erste Pixel ist
          multiplePosition[i] = multiplePosition[i]+1;
          if(multiplePosition[i]>NUMPIXELS+1) {
            multiplePosition[i]=0;
        }
    }
    if (triggerd == true) {
      triggerd=false;
      int fired = 0; // Variable um zu schauen ob schon ausgelöst wurde
       for (int i = 0; i < MAXPOSITIONS; i++) { //alle positionen durchlaufen und eine finden die noch 0 ist und nicht gestartet wurde
         if (multiplePosition[i] == 0) {
           if (fired==0) { //nur dann noch eins auslösen, wennn noch keins ausgelöst wurde
             multiplePosition[i] = multiplePosition[i]+1; // 0 ist ruhezustand, ab 1 läuft es hoch
             fired = 1; //verhindern das noch eins ausgelöst wurde.
           }
        } 
      }   
    }
      
  }
   FastLED.show();
   delay(40);

}
void receiveEvent() {
  count=0;
  while (0 < Wire.available()) {
   // loop through all but the last
    command+=(char)Wire.read(); // receive byte as a character       // print the character
  }
  triggerd=true;
  if (command.toInt()>0)snare=true;
  else snare=false;

}

