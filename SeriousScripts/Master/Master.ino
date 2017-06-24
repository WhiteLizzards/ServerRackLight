/*
 * Master by WhiteLizards
 * 
 * Script that handles the audio and poti input and sends them to the slave Arduinos
 * 
 */

#include <Wire.h>

#define PAYLOAD_SIZE 2        // how many bytes to expect from each I2C salve node
#define NODE_MAX 2            // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 2          // The starting I2C address of slave nodes
#define NODE_READ_DELAY 1000  // Some delay between I2C node reads

int nodePayload[PAYLOAD_SIZE];

void setup() {
  Serial.begin(9600);
  PrintStartMessage();
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop() {

//  for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) {
//    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);
//    if(Wire.available() == PAYLOAD_SIZE) {
//    }
//  }
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  Wire.beginTransmission(7); // transmit to device #8
  Wire.write("y is ");        // sends five bytes
  Wire.write(x+5);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
  
}


// Functions
// Prints the Start Message
void PrintStartMessage() {
  Serial.println("MASTER READER NODE");
  Serial.print("Maximum Slave Nodes: ");
  Serial.println(NODE_MAX);
  Serial.print("Payload size: ");
  Serial.println(PAYLOAD_SIZE);
  Serial.println("***********************");
}

