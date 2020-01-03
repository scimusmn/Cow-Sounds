//written by Joe Meyer, Fab III at the Science Museum of MN
//Created 5/6/2019 for Gateway to Science in Bismarck, ND

#include "DFPlayerMini_Fast.h"
#include <SoftwareSerial.h>
#include "Button.h"

#define groundedPin 3
#define softSerialTX1 10 
#define softSerialTX2 11 
#define softSerialTX3 12 
#define softSerialTX4 13

#define heart_btn_pin 4
#define lung_btn_pin 8
#define gut_btn_pin 12
#define moo_btn_pin 0

#define heart_led_pin 5
#define lung_led_pin 9
#define gut_led_pin 13


Button heart_btn;
Button lung_btn;
Button gut_btn;
Button moo_btn;


DFPlayerMini_Fast HeartPlayer;  // create audio player "DFplayer1"
DFPlayerMini_Fast LungPlayer;  // create audio player "DFplayer2"
DFPlayerMini_Fast GutPlayer;  // create audio player "DFplayer3"
DFPlayerMini_Fast HealthyPlayer;  // create audio player "DFplayer4"
SoftwareSerial HeartSerial(groundedPin, softSerialTX1); // open software serial
SoftwareSerial LungSerial(groundedPin, softSerialTX2); // open software serial
SoftwareSerial GutSerial(groundedPin, softSerialTX3); // open software serial
SoftwareSerial HealthySerial(groundedPin, softSerialTX4); // open software serial

void setup() {

  Serial.begin(9600);
  HeartSerial.begin(9600);
  LungSerial.begin(9600);
  GutSerial.begin(9600);
  HealthySerial.begin(9600);

  HeartPlayer.begin(HeartSerial);
  LungPlayer.begin(LungSerial);
  GutPlayer.begin(GutSerial);
  HealthyPlayer.begin(HealthySerial);
  
  HeartPlayer.volume(30); // max volume is 30
  delay(80);
  LungPlayer.volume(30); // max volume is 30
  delay(80);
  GutPlayer.volume(30); // max volume is 30
  delay(80);
  HealthyPlayer.volume(30); // max volume is 30
  delay(80);
    
  Serial.println("Cow Sounds");

  heart_btn.setup(heart_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(1);
      delay(50);
    }
  });

  lung_btn.setup(lung_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(2);
      delay(50);
    }
  });

  gut_btn.setup(gut_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(3);
      delay(50);
    }
  });

  moo_btn.setup(moo_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(4);
      delay(50);
    }
  });


//  DFplayer1.loop(1);
//  delay(80);
//  DFplayer2.loop(1);
//  delay(80);
//  DFplayer3.loop(1);
//  delay(80);
}

void loop() {
  heart_btn.idle();
  lung_btn.idle();
  gut_btn.idle();
  moo_btn.idle();
 
}
