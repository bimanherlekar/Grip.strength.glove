

/* FSR simple testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
#include <Wire.h>
#include "Adafruit_DRV2605.h"

int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 1;
int fsrPin3 = 2;
int fsrReading1;     // the analog reading from the FSR resistor divider
int fsrReading2; 
int fsrReading3;
int fsrReading;
int speakerPin = 8;      // connect Red LED to pin 8 (PWM pin)
int speakerMap;
Adafruit_DRV2605 drv;


void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 

  drv.begin();
  
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG); 
}
 
void loop(void) {
 uint8_t effect = 1;
 fsrReading1 = analogRead(fsrPin);  
 fsrReading2 = analogRead(fsrPin2);
 fsrReading3 = analogRead(fsrPin3);
 Serial.print("Analog reading = ");
 Serial.print(fsrReading1);     // the raw analog reading
 Serial.print(",");
 Serial.print(fsrReading2);
 Serial.print(",");
 Serial.print(fsrReading3);
 fsrReading = (fsrReading1+fsrReading2)/2.0;
 fsrReading = (fsrReading+fsrReading3)/2.0;
 speakerMap = map(fsrReading, 0, 1000, 120, 1500);
 
 
 // We'll have a few threshholds, qualitatively determined
  if (fsrReading < 10) 
  {
    Serial.println(" - No pressure");
  } 
  else if (fsrReading < 350) 
  {
    Serial.println(" - Light touch");
    
  } 
  else if (fsrReading < 700) 
  {
    Serial.println(" - Light squeeze");
     //effect = 50;
  } 
  else if (fsrReading < 950)
  {
    Serial.println(" - Medium squeeze");
     effect = 49;
  } 
  else if(fsrReading < 990) 
  {
    Serial.println(" - Big squeeze");
    effect = 48;
  }
  else
  {
    effect = 47;
    Serial.println(" - Danger!!!");
  }

if(effect != 1)
{
  // set the effect to play
  drv.setWaveform(0, effect);  // play effect 
  drv.setWaveform(1, 0);       // end waveform
  tone(speakerPin, speakerMap,10);
  // play the effect!
  drv.go();
  
}
  
  
  delay(50);
} 
