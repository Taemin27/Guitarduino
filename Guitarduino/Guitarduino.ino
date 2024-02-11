// Define page orders
#define page0_setup tuner_setup
#define page0_loop tuner_loop

#define page1_setup effects_setup
#define page1_loop effects_loop

#define page2_setup metronome_setup
#define page2_loop metronome_loop

#define page3_setup backingTrack_setup
#define page3_loop backingTrack_loop

#define page4_setup record_setup
#define page4_loop record_loop

// Include Statements
#include <Adafruit_GFX_Buffer.h>  // https://github.com/vjmuzik/Adafruit_GFX_Buffer.git
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>  // One character at size 1 = 6 * 8 pixels
#include <Encoder.h>
#include <Bounce2.h>
#include "SystemBitmaps.h"

// Audio
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc dc1;             //xy=251.1999969482422,543
AudioInputI2S i2s1;                   //xy=258.1999969482422,336
AudioAmplifier notefreqAmp;           //xy=449.1999969482422,261
AudioEffectWaveFolder wavefolder1;    //xy=566.2001266479492,523.999981880188
AudioAmplifier distortionLevelAmp;    //xy=570.2001876831055,599.9999837875366
AudioMixer4 overdriveMixer;           //xy=571.1999969482422,471
AudioFilterBiquad overdriveBiquad;    //xy=571.2001266479492,561.9999828338623
AudioAmplifier distortionGainAmp;     //xy=572.2001304626465,638.9999828338623
AudioAmplifier overdriveLevelAmp;     //xy=572.2000617980957,681.0000009536743
AudioAmplifier overdriveGainAmp;      //xy=576.2001266479492,721.9999837875366
AudioAnalyzeNoteFrequency notefreq1;  //xy=605.1999969482422,263
AudioAmplifier delayAmp;              //xy=883.1999282836914,610.0000114440918
AudioMixer4 delayMixer;               //xy=967.1999282836914,476.0000114440918
AudioEffectDelay delay1;              //xy=1018.1999282836914,633.0000114440918
AudioMixer4 reverbMixer;              //xy=1292.1999282836914,475.0000114440918
AudioEffectFreeverb freeverb1;        //xy=1292.1999740600586,526.9999809265137
AudioAmplifier reverbAmp;             //xy=1296.1999778747559,564.999981880188
AudioSynthSimpleDrum metronomeDrum;   //xy=1732.4444046020508,441.1111249923706
AudioMixer4 masterMixer;              //xy=1919.8888702392578,449.1111869812012
AudioOutputI2S i2s2;                  //xy=2082.1997833251953,443.0000419616699
AudioConnection patchCord1(dc1, 0, wavefolder1, 1);
AudioConnection patchCord2(i2s1, 1, notefreqAmp, 0);
AudioConnection patchCord3(i2s1, 1, overdriveMixer, 0);
AudioConnection patchCord4(i2s1, 1, overdriveGainAmp, 0);
AudioConnection patchCord5(notefreqAmp, notefreq1);
AudioConnection patchCord6(wavefolder1, 0, overdriveMixer, 1);
AudioConnection patchCord7(distortionLevelAmp, overdriveBiquad);
AudioConnection patchCord8(overdriveMixer, 0, delayMixer, 0);
AudioConnection patchCord9(overdriveBiquad, 0, wavefolder1, 0);
AudioConnection patchCord10(distortionGainAmp, distortionLevelAmp);
AudioConnection patchCord11(overdriveLevelAmp, distortionGainAmp);
AudioConnection patchCord12(overdriveGainAmp, overdriveLevelAmp);
AudioConnection patchCord13(delayAmp, delay1);
AudioConnection patchCord14(delayMixer, 0, reverbMixer, 0);
AudioConnection patchCord15(delayMixer, reverbAmp);
AudioConnection patchCord16(delayMixer, delayAmp);
AudioConnection patchCord17(delay1, 0, delayMixer, 1);
AudioConnection patchCord18(reverbMixer, 0, masterMixer, 3);
AudioConnection patchCord19(freeverb1, 0, reverbMixer, 1);
AudioConnection patchCord20(reverbAmp, freeverb1);
AudioConnection patchCord21(metronomeDrum, 0, masterMixer, 2);
AudioConnection patchCord22(masterMixer, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=138.1999969482422,336
// GUItool: end automatically generated code





// Display
#define CS 4
#define DC 5
#define RST 9

//Adafruit_ST7735 display = Adafruit_ST7735(CS, DC, RST);
Adafruit_GFX_Buffer<Adafruit_ST7735> display = Adafruit_GFX_Buffer<Adafruit_ST7735>(80, 160, Adafruit_ST7735(&SPI, CS, DC, RST));

const uint16_t BLACK = 0x0000;
const uint16_t WHITE = 0xffff;
const uint16_t GRAY = 0x8430;
const uint16_t BLUE = 0x001f;
const uint16_t RED = 0xF800;
const uint16_t YELLOW = 0xffe0;
const uint16_t GREEN = 0x07e0;

// Encoder
Encoder enc(2, 3);
long oldPosition = 0;

const int buttonPin = 1;
Bounce bounce = Bounce();


// Count pages from 0
int currentPage = 0;
int pageCount = 4;
bool pageSelected = false;


// Metronome global variables
bool metronome_on = false;
float metronome_previousMillis;
int metronome_bpm = 100;
int metronome_beatsPerBar = 4;
int metronome_currentBeat = 0;


void setup() {
  AudioNoInterrupts();

  /* System */
  Serial.begin(9600);
  bounce.attach(buttonPin, INPUT_PULLUP);
  bounce.interval(5);

  /* Display */
  display.initR(INITR_MINI160x80);
  display.setRotation(3);
  display.invertDisplay(true);

  /* Audio */
  AudioMemory(700);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(1);
  sgtl5000_1.adcHighPassFilterDisable();

  masterMixer.gain(0, 1);
  masterMixer.gain(1, 1);
  masterMixer.gain(2, 1);
  masterMixer.gain(3, 1);

  /* Tuner */
  notefreqAmp.gain(0);
  notefreq1.begin(0.15);

  /* Effects */
  //Drive
  dc1.amplitude(0.1);
  ef_drive_disable();

  //Delay
  delayAmp.gain(0);
  delayMixer.gain(0, 1);
  delayMixer.gain(1, 0);
  for (int i = 1; i < 7; i++) {
    delay1.disable(i);
  }

  //Freeverb
  reverbAmp.gain(0);
  reverbMixer.gain(0, 1);
  reverbMixer.gain(1, 0);
  freeverb1.roomsize(0);
  freeverb1.damping(0);

  /* Metronome */
  metronomeDrum.pitchMod(0.5);
  metronomeDrum.length(50);



  AudioInterrupts();

  page0_setup();
}

int previousMemoryUsage = 0;

void loop() {
  printAudioMemoryUsage();

  switch (currentPage) {
    case 0:
      page0_loop();
      break;
    case 1:
      page1_loop();
      break;
    case 2:
      page2_loop();
      break;
    case 3:
      page3_loop();
      break;
    case 4:
      page4_loop();
      break;
  }

  if (!pageSelected) {
    int encoder = readEncoder();
    if (encoder != 0) {
      switchPage(currentPage + encoder);
    }
  }


  // Metronome
  if (metronome_on) {
    float currentMillis = millis();
    if (currentMillis - metronome_previousMillis >= 60000 / metronome_bpm) {
      if (++metronome_currentBeat > metronome_beatsPerBar || metronome_currentBeat == 1) {
        metronome_currentBeat = 1;
        metronomeDrum.frequency(440);
        metronomeDrum.noteOn();
      } else {
        metronomeDrum.frequency(220);
        metronomeDrum.noteOn();
      }
      if (currentPage == 2 && pageSelected) {
        metronome_drawIndicator();
        display.display();
      }
      metronome_previousMillis = currentMillis;
    }
  }
}

void switchPage(int page) {
  if (0 <= page && page <= pageCount) {
    currentPage = page;
    switch (page) {
      case 0:
        page0_setup();
        break;
      case 1:
        page1_setup();
        break;
      case 2:
        page2_setup();
        break;
      case 3:
        page3_setup();
        break;
      case 4:
        page4_setup();
        break;
    }
  }
}

void drawArrows() {
  if (currentPage > 0) {
    display.drawBitmap(0, 29, leftArrow, 13, 22, WHITE);
  }
  if (currentPage < pageCount) {
    display.drawBitmap(147, 29, rightArrow, 13, 22, WHITE);
  }
}

long readEncoder() {
  long newPosition = round(enc.read() / 4);
  if (newPosition - oldPosition > 0) {
    oldPosition = newPosition;
    return (1);
  } else if (newPosition - oldPosition < 0) {
    oldPosition = newPosition;
    return (-1);
  }
  return (0);
}

void printAudioMemoryUsage() {
  int memoryUsage = AudioMemoryUsage();
  if (memoryUsage != previousMemoryUsage) {
    previousMemoryUsage = memoryUsage;
    Serial.println(memoryUsage);
  }
}
