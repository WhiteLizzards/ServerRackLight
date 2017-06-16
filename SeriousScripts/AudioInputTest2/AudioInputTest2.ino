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

#define FILTER_FREQUENCY (222)

const int ledPin = 6;

int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];

int buttonState = LOW;
int lastState = LOW;
int realInput;

unsigned long delayval = 100;
unsigned long previousMillis = 0;
unsigned long currentMillis;
boolean triggered = false;
int i = 0;


int multiplePosition[NUMPIXELS];

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

  for(int i = 0; i < NUMPIXELS; ++i){
      multiplePosition[i] = 0;  
  }
  
}

int real_input(){
   return Frequencies_One[0]; // 0 - 1024
}

int filter_frequency(int input, int by){
  if(input < by){
     return input;
  }

  return -1;
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

void loop() {
  
    Read_Frequencies();
    realInput = real_input(); // / 255; 
    
    int filter = 200;

    currentMillis = millis();

    if (realInput >= filter) {
      triggered = true;
    }
    else {
      triggered = false;
    }
    
    previousMillis = currentMillis;
    
    if (triggered) {
      if ((currentMillis - previousMillis) % delayval == 0) { 

        
        for(int j = 0; j < NUMPIXELS; ++j){
          //i = j;

          pixels.setPixelColor(i, pixels.Color(0, realInput%255, 0));
          if (i!=0) 
            pixels.setPixelColor(i-1, pixels.Color(0,0,0));
            
          pixels.show();
          if (i == NUMPIXELS) {
              i = 0;
          }
          delay(0);
          i++;
        }
        
      }
    }
        
        
        
    

    /*
    if (real_input >= filter) {
      
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, realInput%255, 0));
        
      }
      
    } else {
      
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        
      }
      
    }
    */
   
    

  Serial.print("real_input() ");
  Serial.println(realInput);
  Serial.print("Filter Real ");
  Serial.println(filter_frequency(realInput, FILTER_FREQUENCY));

}

/*
void loop() {
  Read_Frequencies();

  if (Frequencies_One[0] >=200){
    buttonState == HIGH;
  }
  else {
    buttonState == LOW;
  }
  
  if (buttonState != lastState){
    Serial.println(lastState);
    lastState = buttonState;
    }
    for ( int i=0;i<NUMPIXELS;i++){ //schaue in allen Positionen nach // check all Pos
        
        if (multiplePosition[i]>0){ 
          
          if (buttonState == HIGH){
             
            pixels.setPixelColor(multiplePosition[i]-1, pixels.Color(0,255,0)); //gib an die aktuelle Position-1 eine Farbe
            //lastState2 = buttonState2;
          }
          
          if (multiplePosition[i]>1) 
            pixels.setPixelColor(multiplePosition[i]-2, pixels.Color(0,0,0)); //stelle die Position -2 auf schwarz, aber nur dann wenn es nicht das erste Pixel ist
          multiplePosition[i] = multiplePosition[i]+1;
          if(multiplePosition[i]>NUMPIXELS+1) 
            multiplePosition[i]=0;
        }
    }
    
    if (buttonState == HIGH) {
          int fired = 0; // Variable um zu schauen ob schon ausgelöst wurde
          for (int i = 0; i < NUMPIXELS; i++) { //alle positionen durchlaufen und eine finden die noch 0 ist und nicht gestartet wurde
            if (multiplePosition[i] == 0) {
              if (fired==0) { //nur dann noch eins auslösen, wennn noch keins ausgelöst wurde
                multiplePosition[i] = multiplePosition[i]+1; //auslösen
                fired = 1; //verhindern das noch eins ausgelöst wurde.
              }
            } 
          }
          
    }
  pixels.show();
  delay(100);

  
  



  //Serial.println(Frequencies_One[0]);
  //Serial.println(Frequencies_One[1]);
  //Serial.println(Frequencies_One[2]);
  //Serial.println(Frequencies_One[3]);
  //Serial.println(Frequencies_One[4]);
  //Serial.println(Frequencies_One[5]);
  //Serial.println(Frequencies_One[6]);
  //Graph_Frequencies();
 

}
*/




