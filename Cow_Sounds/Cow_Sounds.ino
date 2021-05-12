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
// #define audioPin A5  //NOT WORKING

#define moo_btn_pin 9

unsigned long currentMillis;
unsigned long lastActivityMillis;
int i = 0;
long millisToSwitchAudio = 300000; //
long millisMooStarted = 0;

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
  // pinMode(audioPin, INPUT);

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

  moo_btn.setup(moo_btn_pin, [](int state)
                {
                  if (state == 1)
                  {
                    MooPlayer.play(1);
                    millisMooStarted = millis();
                  }
                });

  changeAudio();
}

void loop()
{

  if ((millis() - millisMooStarted) > 3000)
    moo_btn.idle();

  // int sound = analogRead(audioPin);
  // if (sound > 600)
  // { // audio signal is biased at 512 (2.5V)
  //   // lastActivityMillis = millis();
  // }

  if ((millis() - lastActivityMillis) > millisToSwitchAudio)
  {
    changeAudio();
    millisToSwitchAudio = random(300000, 900000); // moo and switch audio 5 -15 min
  }
}

void changeAudio()
{
  MooPlayer.play(1);
  millisMooStarted = millis();
  delay(80);

  i = random(6);          //random number between 0 and 5
  i = constrain(i, 1, 5); // odds of playing track 1 (healthy) are 2 out of 6
  LungPlayer.loop(i);     //
  delay(80);
  Serial.print("Lung ");
  Serial.print(i);

  i = random(5);          //random number between 0 and 4
  i = constrain(i, 1, 4); // odds of playing track 1 (healthy) are 2 out of 5
  GutPlayer.loop(i);
  delay(80);
  Serial.print(", Gut ");
  Serial.print(i);

  i = random(6);          //random number between 0 and 5
  i = constrain(i, 1, 5); // odds of playing track 1 (healthy) are 2 out of 6
  HeartPlayer.loop(i);
  delay(80);
  Serial.print(", Heart ");
  Serial.println(i);

  lastActivityMillis = millis();
}
