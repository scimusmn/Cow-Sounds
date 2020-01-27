//written by Joe Meyer, Fab III at the Science Museum of MN
//Created 5/6/2019 for Gateway to Science in Bismarck, ND

#include "DFPlayerMini_Fast.h"
#include <SoftwareSerial.h>
#include "Button.h"

#define fakeRx A2
#define softSerialTX1 1 
#define softSerialTX2 2
#define softSerialTX3 6 
#define softSerialTX4 10

#define heart_btn_pin 4
#define lung_btn_pin 8
#define gut_btn_pin 12
#define moo_btn_pin 0

#define heart_led_pin 5
#define lung_led_pin 9
#define gut_led_pin 13

unsigned long currentMillis;
unsigned long lastActivityMillis;
long millisToSwitchAudio = 300000;  // 300000 = 5 min. Audio tracks won't switch unless no activity is detected for this many millis

Button heart_btn;
Button lung_btn;
Button gut_btn;
Button moo_btn;

DFPlayerMini_Fast HeartPlayer; 
DFPlayerMini_Fast LungPlayer;  
DFPlayerMini_Fast GutPlayer; 
DFPlayerMini_Fast HealthyPlayer; 

SoftwareSerial HeartSerial(fakeRx, softSerialTX1); // open software serial
SoftwareSerial LungSerial(fakeRx, softSerialTX2); // open software serial
SoftwareSerial GutSerial(fakeRx, softSerialTX3); // open software serial
SoftwareSerial HealthySerial(fakeRx, softSerialTX4); // open software serial

void setup() {
  pinMode(fakeRx, INPUT);
  
  HeartSerial.begin(9600);
  LungSerial.begin(9600);
  GutSerial.begin(9600);
  HealthySerial.begin(9600);

  delay(100);

  HeartPlayer.begin(HeartSerial);
  LungPlayer.begin(LungSerial);
  GutPlayer.begin(GutSerial);
  HealthyPlayer.begin(HealthySerial);

  delay(100);
  
  HeartPlayer.volume(30); // max volume is 30
  delay(100);
  LungPlayer.volume(30); // max volume is 30
  delay(100);
  GutPlayer.volume(30); // max volume is 30
  delay(100);
  HealthyPlayer.volume(30); // max volume is 30
  delay(100);
    
  heart_btn.setup(heart_btn_pin, [](int state) {
    if (state == 1) {      
      HealthyPlayer.play(1);
      delay(40);
      lastActivityMillis = millis();
    }
  });

  lung_btn.setup(lung_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(2);
      delay(40);
      lastActivityMillis = millis();
    }
  });

  gut_btn.setup(gut_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(3);
      delay(40);
      lastActivityMillis = millis();
    }
  });

  moo_btn.setup(moo_btn_pin, [](int state) {
    if (state == 1) {
      HealthyPlayer.play(4);
      delay(100);
      lastActivityMillis = millis();
    }
  });

    HeartPlayer.loop(1);
    delay(100);
    LungPlayer.loop(1);
    delay(100);
    GutPlayer.loop(1);
    delay(100);
}

void loop() {

  
//  if ((millis()-lastActivityMillis) > millisToSwitchAudio){
//  //no activity for a while, skip each player ahead random num of tracks.  
//    for (int i = 0; i < random(3); i++) {
//      HeartPlayer.playNext();
//      delay(100);
//    }
//
//    for (int i = 0; i < random(3); i++) {
//      LungPlayer.playNext();
//      delay(100);
//    }
//
//    for (int i = 0; i < random(3); i++) {
//      GutPlayer.playNext();
//      delay(100);
//    }
//    lastActivityMillis = millis();
//  }
  
  heart_btn.idle();
  lung_btn.idle();
  gut_btn.idle();
  moo_btn.idle();
 
}
