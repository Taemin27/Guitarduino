#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=643,397
AudioAmplifier           amp1;           //xy=845,386
AudioEffectWaveshaper    waveshape1;     //xy=1044,474
AudioMixer4              mixer1;         //xy=1213,382
AudioOutputI2S           i2s2;           //xy=1420,379
AudioConnection          patchCord1(i2s1, 1, amp1, 0);
AudioConnection          patchCord2(amp1, waveshape1);
AudioConnection          patchCord3(amp1, 0, mixer1, 0);
AudioConnection          patchCord4(waveshape1, 0, mixer1, 1);
AudioConnection          patchCord5(mixer1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1036,249
// GUItool: end automatically generated code



#define COUNT_OF(x) ((int32_t)(sizeof x / sizeof x[0]))

bool bypass = true;

float shape[] =  {-1.0, -0.9, 0.0, 0.7, 0.9, 1.0, 1.2, 1.0, 0.8};

void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT_PULLUP);

  AudioMemory(100);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

  mixer1.gain(0, 1);
  mixer1.gain(1, 0);

  amp1.gain(1.5);

  //waveform1.begin(1, 220, WAVEFORM_SINE);

  waveshape1.shape(shape,COUNT_OF(shape));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(1) == LOW) {
    bypass = !bypass;
    if(bypass) {
      mixer1.gain(0, 1);
      mixer1.gain(1, 0);
      Serial.println("Bypass on");
    } else {
      mixer1.gain(0, 0);
      mixer1.gain(1, 1);
      Serial.println("Bypass off");
    }
    delay(300);
  }
}
