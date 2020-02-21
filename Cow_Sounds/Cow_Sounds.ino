//written by Joe Meyer, Fab III at the Science Museum of MN
//Created 5/6/2019 for Gateway to Science in Bismarck, ND

#include "DFPlayerMini_Fast.h"
#include <SoftwareSerial.h>
#include "Button.h"

#define fakeRx 3
#define softSerialTX1 1 
#define softSerialTX2 2
#define softSerialTX3 6 
#define softSerialTX4 10

#define moo_btn_pin 0

unsigned long currentMillis;
unsigned long lastActivityMillis;
long millisToSwitchAudio = 30000;  // 300000 = 5 min. Audio tracks won't switch unless no activity is detected for this many millis

Button moo_btn;

DFPlayerMini_Fast HeartPlayer; 
DFPlayerMini_Fast LungPlayer;  
DFPlayerMini_Fast GutPlayer; 
DFPlayerMini_Fast MooPlayer; 

SoftwareSerial HeartSerial(fakeRx, softSerialTX1); // open software serial
SoftwareSerial LungSerial(fakeRx, softSerialTX2); // open software serial
SoftwareSerial GutSerial(fakeRx, softSerialTX3); // open software serial
SoftwareSerial MooSerial(fakeRx, softSerialTX4); // open software serial

void setup() {
  pinMode(fakeRx, INPUT);
  
  HeartSerial.begin(9600);
  LungSerial.begin(9600);
  GutSerial.begin(9600);
  MooSerial.begin(9600);

  delay(80);

  HeartPlayer.begin(HeartSerial);
  delay(80);
  LungPlayer.begin(LungSerial);
  delay(80);
  GutPlayer.begin(GutSerial);
  delay(80);
  MooPlayer.begin(MooSerial);

  delay(80);
  
  HeartPlayer.volume(30); // max volume is 30
  delay(80);
  LungPlayer.volume(30); // max volume is 30
  delay(80);
  GutPlayer.volume(30); // max volume is 30
  delay(80);
  MooPlayer.volume(30); // max volume is 30
  delay(80);

  moo_btn.setup(moo_btn_pin, [](int state) {
    if (state == 1) {      
      MooPlayer.play(1);
      delay(80);
    }
  });
  
  HeartPlayer.loop(1);
  delay(80);
  LungPlayer.loop(1);
  delay(80);
  GutPlayer.loop(1);
  delay(80);
}

void loop() {
  
  if ((millis()-lastActivityMillis) > millisToSwitchAudio){
    MooPlayer.play(1);
    LungPlayer.playNext();
    GutPlayer.playNext();
    HeartPlayer.playNext();
    lastActivityMillis = millis();
  }
//
//    for (int i = 0; i < random(3); i++) {
//      LungPlayer.playNext();
//      delay(80);
//    }
//
//    for (int i = 0; i < random(3); i++) {
//      GutPlayer.playNext();
//      delay(80);
//    }
//    lastActivityMillis = millis();
//  }
  
  moo_btn.idle();
 
}
