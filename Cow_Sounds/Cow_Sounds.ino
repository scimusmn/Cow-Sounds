//written by Joe Meyer, Fab III at the Science Museum of MN
//Created 5/6/2019 for Gateway to Science in Bismarck, ND

#include "DFPlayerMini_Fast.h"
#include <SoftwareSerial.h>
#include "Button.h"

#define fakeRx 13
#define softSerialTX1 7
#define softSerialTX2 6
#define softSerialTX3 5
#define softSerialTX4 4
#define audioPin A5

#define moo_btn_pin 9

unsigned long currentMillis;
unsigned long lastActivityMillis;
int i = 0;
long millisToSwitchAudio = 30000; // 300000 = 5 min. Audio tracks won't switch unless no activity is detected for this many millis

Button moo_btn;

DFPlayerMini_Fast HeartPlayer;
DFPlayerMini_Fast LungPlayer;
DFPlayerMini_Fast GutPlayer;
DFPlayerMini_Fast MooPlayer;

SoftwareSerial HeartSerial(fakeRx, softSerialTX1); // open software serial
SoftwareSerial LungSerial(fakeRx, softSerialTX2);  // open software serial
SoftwareSerial GutSerial(fakeRx, softSerialTX3);   // open software serial
SoftwareSerial MooSerial(fakeRx, softSerialTX4);   // open software serial

void setup()
{
  Serial.begin(9600);
  Serial.println("hi");
  pinMode(fakeRx, INPUT);
  pinMode(audioPin, INPUT);

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
    if (state == 1)
    {
      Serial.println("Moo");
      changeAudio();
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

void loop()
{

  moo_btn.idle();

  int sound = analogRead(audioPin);
  if (sound > 600)
  { // audio signal is biased at 512 (2.5V)
    // lastActivityMillis = millis();
  }

  if ((millis() - lastActivityMillis) > millisToSwitchAudio)
  {
    changeAudio();
  }
}

void changeAudio(){
  MooPlayer.play(1);
    delay(80);
    i++;
    if (i == 4)
      i = 1;
    Serial.print("track: ");
    Serial.println(i);
    LungPlayer.loop(i); // random(3) + 1);
    delay(80);
    GutPlayer.loop(i); //random(3) + 1);
    delay(80);
    HeartPlayer.loop(i); //random(3) + 1);

    lastActivityMillis = millis();
}
