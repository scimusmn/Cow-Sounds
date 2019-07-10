//written by Joe Meyer, Fab III at the Science Museum of MN
//Created 5/6/2019 for Gateway to Science in Bismarck, ND

#include "DFPlayerMini_Fast.h"
#include <SoftwareSerial.h>

#define DF_busy_pin 12  
#define softSerialRX1 1
#define softSerialTX1 10 
#define softSerialRX2 1
#define softSerialTX2 11 
#define softSerialRX3 1
#define softSerialTX3 12 
#define softSerialRX4 1
#define softSerialTX4 13

#define knockSensor A0 // the piezo is connected to analog pin 0
#define threshold 20  // threshold value to decide when the detected sound is a knock or not


DFPlayerMini_Fast DFplayer1;  // create audio player "DFplayer1"
DFPlayerMini_Fast DFplayer2;  // create audio player "DFplayer2"
DFPlayerMini_Fast DFplayer3;  // create audio player "DFplayer3"
DFPlayerMini_Fast DFplayer4;  // create audio player "DFplayer4"
SoftwareSerial mySerial1(softSerialRX1, softSerialTX1); // open software serial
SoftwareSerial mySerial2(softSerialRX2, softSerialTX2); // open software serial
SoftwareSerial mySerial3(softSerialRX3, softSerialTX3); // open software serial
SoftwareSerial mySerial4(softSerialRX4, softSerialTX4); // open software serial


int is_Healthy = 1;
int sensorReading = 0; 
unsigned long millisLastKnock;

void setup() {

  Serial.begin(9600);
  mySerial1.begin(9600);
  mySerial2.begin(9600);
  mySerial3.begin(9600);
  mySerial4.begin(9600);

  //pinMode(DF_busy_pin, INPUT_PULLUP);
  pinMode(knockSensor, INPUT);

  DFplayer1.begin(mySerial1);
  DFplayer2.begin(mySerial2);
  DFplayer3.begin(mySerial3);
  DFplayer4.begin(mySerial4);
  
  DFplayer1.volume(30); // max volume is 30
  delay(80);
  DFplayer2.volume(30); // max volume is 30
  delay(80);
  DFplayer3.volume(30); // max volume is 30
  delay(80);
  DFplayer4.volume(30); // max volume is 30
  delay(80);
    
  Serial.println("Cow Sounds");

  DFplayer1.loop(1);
  delay(80);
  DFplayer2.loop(1);
  delay(80);
  DFplayer3.loop(1);
  delay(80);
}

void loop() {
  sensorReading = analogRead(knockSensor);

  if (sensorReading >= threshold) { //knock detected
    millisLastKnock = millis();  // store time stamp of knock
    DFplayer4.play(is_Healthy);  // play healthy or not healthy sound
    delay(20);
  }

  if (30000 < (millis() - millisLastKnock)){ // if there's 30 sec without a knock, change healthy?
    millisLastKnock = millis();
    is_Healthy = random(1,3); // randomly choose 1 or 2 (if cow is healthy or not).
  }

}
