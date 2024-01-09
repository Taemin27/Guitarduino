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
#include <Adafruit_GFX.h>     // One character at size 1 = 6 * 8 pixels
#include <Encoder.h>
#include "SystemBitmaps.h"

// Audio 
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=261.1999816894531,532.2000122070312
AudioAmplifier           notefreqAmp;    //xy=452.1999816894531,457.20001220703125
AudioSynthWaveformDc     overdriveDC;            //xy=588.2002382278442,820.2000331878662
AudioMixer4              overdriveMixer;         //xy=590.2000389099121,658.2000312805176
AudioFilterBiquad        overdriveBiquad;        //xy=590.200065612793,720.2000303268433
AudioEffectWaveFolder    overdriveWaveFolder;    //xy=591.2001800537109,771.2000331878662
AudioAnalyzeNoteFrequency notefreq1;      //xy=608.1999816894531,459.20001220703125
AudioAmplifier           delayAmp;       //xy=865.2000427246094,790.200029373169
AudioMixer4              delayMixer;     //xy=949.2000427246094,656.200029373169
AudioEffectDelay         delay1;         //xy=1000.2000427246094,813.200029373169
AudioEffectFreeverb      freeverb1;      //xy=1269.2000427246094,715.200029373169
AudioMixer4              reverbMixer;    //xy=1274.2000427246094,655.200029373169
AudioAmplifier           reverbAmp;      //xy=1278.2000427246094,765.200029373169
AudioOutputI2S           i2s2;           //xy=1544.2001266479492,645.200029373169
AudioConnection          patchCord1(i2s1, 1, notefreqAmp, 0);
AudioConnection          patchCord2(i2s1, 1, overdriveWaveFolder, 0);
AudioConnection          patchCord3(i2s1, 1, overdriveMixer, 0);
AudioConnection          patchCord4(notefreqAmp, notefreq1);
AudioConnection          patchCord5(overdriveDC, 0, overdriveWaveFolder, 1);
AudioConnection          patchCord6(overdriveMixer, 0, delayMixer, 0);
AudioConnection          patchCord7(overdriveBiquad, 0, overdriveMixer, 1);
AudioConnection          patchCord8(overdriveWaveFolder, overdriveBiquad);
AudioConnection          patchCord9(delayAmp, delay1);
AudioConnection          patchCord10(delayMixer, 0, reverbMixer, 0);
AudioConnection          patchCord11(delayMixer, reverbAmp);
AudioConnection          patchCord12(delayMixer, delayAmp);
AudioConnection          patchCord13(delay1, 0, delayMixer, 1);
AudioConnection          patchCord14(freeverb1, 0, reverbMixer, 1);
AudioConnection          patchCord15(reverbMixer, 0, i2s2, 1);
AudioConnection          patchCord16(reverbAmp, freeverb1);
AudioControlSGTL5000     sgtl5000_1;     //xy=141.19998168945312,532.2000122070312
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



// Count pages from 0
int currentPage = 0;
int pageCount = 4;
bool pageSelected = false;

void setup() {
  AudioNoInterrupts();

  /* System */
  Serial.begin(9600);
  pinMode(1, INPUT_PULLUP);

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

  /* Tuner */
  notefreqAmp.gain(0);
  notefreq1.begin(0.15);

  /* Effects */
  //Overdrive
  overdriveMixer.gain(0, 1);
  overdriveMixer.gain(1, 0);
  overdriveDC.amplitude(0);

  //Delay
  delayAmp.gain(0);
  delayMixer.gain(0, 1);
  delayMixer.gain(1, 0);
  for(int i = 1; i < 7; i++) {
    delay1.disable(i);
  }

  //Freeverb
  reverbAmp.gain(0);
  reverbMixer.gain(0, 1);
  reverbMixer.gain(1, 0);
  freeverb1.roomsize(0);
  freeverb1.damping(0);

  
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
}

void switchPage(int page) {
  if (0 <= page && page <= pageCount) {
    currentPage = page;
  }
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
  if(memoryUsage != previousMemoryUsage) {
    previousMemoryUsage = memoryUsage;
    Serial.println(memoryUsage);
  }
}
