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
AudioInputI2S            i2s1;           //xy=283,857
AudioAmplifier           notefreqAmp;    //xy=292,754
AudioAmplifier           delayAmp;           //xy=440,1061
AudioAnalyzeNoteFrequency notefreq1;      //xy=448,756
AudioMixer4              delayMixer;         //xy=582,910
AudioEffectDelay         delay1;         //xy=583,1062
AudioEffectFreeverb      freeverb1;      //xy=868,965
AudioMixer4              reverbMixer;    //xy=873,905
AudioAmplifier           reverbAmp;           //xy=877,1015
AudioOutputI2S           i2s2;           //xy=1127,901
AudioConnection          patchCord1(i2s1, 1, notefreqAmp, 0);
AudioConnection          patchCord2(i2s1, 1, delayMixer, 0);
AudioConnection          patchCord3(notefreqAmp, notefreq1);
AudioConnection          patchCord4(delayAmp, delay1);
AudioConnection          patchCord5(delayMixer, 0, reverbMixer, 0);
AudioConnection          patchCord6(delayMixer, reverbAmp);
AudioConnection          patchCord7(delayMixer, delayAmp);
AudioConnection          patchCord8(delay1, 0, delayMixer, 1);
AudioConnection          patchCord9(freeverb1, 0, reverbMixer, 1);
AudioConnection          patchCord10(reverbMixer, 0, i2s2, 1);
AudioConnection          patchCord11(reverbAmp, freeverb1);
AudioControlSGTL5000     sgtl5000_1;     //xy=343,631
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

  /* Tuner */
  notefreqAmp.gain(0);
  notefreq1.begin(0.15);

  /* Effects */
  //Freeverb
  reverbAmp.gain(0);
  reverbMixer.gain(0, 1);
  reverbMixer.gain(1, 0);
  freeverb1.roomsize(0);
  freeverb1.damping(0);

  //Delay
  delayAmp.gain(0);
  delayMixer.gain(0, 1);
  delayMixer.gain(1, 0);
  for(int i = 1; i < 7; i++) {
    delay1.disable(i);
  }


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
