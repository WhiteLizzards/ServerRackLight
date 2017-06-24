// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
String command="";
int bass, snare, poti;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
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
      else if(count==2)poti=tmp.toInt();
      count++;
      tmp="";
    }
    else{
      tmp+=(char)command[i];
    }
  }
  Serial.println(command);
  Serial.println("bass:" + (String) bass);
  Serial.println("snare:" + (String) snare);
  Serial.println("poti:" + (String) poti);
  command="";
}
