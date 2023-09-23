#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=196,359
AudioOutputI2S           i2s2;           //xy=528,358
AudioConnection          patchCord1(i2s1, 1, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=218,228
// GUItool: end automatically generated code






void setup() {
  AudioMemory(120);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
