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
#include <Adafruit_GFX_Buffer.h> // https:github.com/vjmuzik/Adafruit_GFX_Buffer.git
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h> // One character at size 1 = 6*8 pixels
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
AudioSynthWaveformDc     dc1;            //xy=303.6666564941406,677.9999923706055
AudioInputI2S            i2s1;           //xy=310.6666564941406,470.99999237060547
AudioAmplifier           notefreqAmp;    //xy=501.6666564941406,395.99999237060547
AudioEffectWaveshaper    waveshape1;     //xy=505.93334197998047,590.9334487915039
AudioAnalyzeNoteFrequency notefreq1;      //xy=657.6666564941406,397.99999237060547
AudioEffectWaveFolder    wavefolder1;    //xy=700.666690826416,644.000057220459
AudioAmplifier           distortionLevelAmp; //xy=704.666690826416,720.000057220459
AudioFilterBiquad        overdriveBiquad; //xy=705.666690826416,682.000057220459
AudioAmplifier           distortionGainAmp; //xy=706.666690826416,759.000057220459
AudioAmplifier           overdriveLevelAmp; //xy=706.666690826416,802.000057220459
AudioMixer4              overdriveMixer; //xy=709.666633605957,590.9999923706055
AudioAmplifier           overdriveGainAmp; //xy=710.666690826416,842.000057220459
AudioAmplifier           delayAmp;       //xy=935.6666564941406,744.9999923706055
AudioMixer4              delayMixer;     //xy=1019.6666564941406,610.9999923706055
AudioEffectDelay         delay1;         //xy=1070.6666564941406,767.9999923706055
AudioMixer4              reverbMixer;    //xy=1344.6666564941406,609.9999923706055
AudioEffectFreeverb      freeverb1;      //xy=1344.6666564941406,660.9999923706055
AudioAmplifier           reverbAmp;      //xy=1348.6666564941406,698.9999923706055
AudioPlaySdWav           playSdWav1;     //xy=1473.3333549499512,432.66669273376465
AudioSynthSimpleDrum     metronomeDrum;  //xy=1633.6667098999023,536.9999752044678
AudioMixer4              playSDMixer;         //xy=1688.3333892822266,442.66669273376465
AudioMixer4              masterMixer;    //xy=1971.6666564941406,583.9999923706055
AudioOutputI2S           i2s2;           //xy=2134.6666564941406,577.9999923706055
AudioConnection          patchCord1(dc1, 0, wavefolder1, 1);
AudioConnection          patchCord2(i2s1, 1, notefreqAmp, 0);
AudioConnection          patchCord3(i2s1, 1, overdriveMixer, 0);
AudioConnection          patchCord4(i2s1, 1, overdriveGainAmp, 0);
AudioConnection          patchCord5(i2s1, 1, waveshape1, 0);
AudioConnection          patchCord6(notefreqAmp, notefreq1);
AudioConnection          patchCord7(waveshape1, 0, overdriveMixer, 2);
AudioConnection          patchCord8(wavefolder1, 0, overdriveMixer, 1);
AudioConnection          patchCord9(distortionLevelAmp, overdriveBiquad);
AudioConnection          patchCord10(overdriveBiquad, 0, wavefolder1, 0);
AudioConnection          patchCord11(distortionGainAmp, distortionLevelAmp);
AudioConnection          patchCord12(overdriveLevelAmp, distortionGainAmp);
AudioConnection          patchCord13(overdriveMixer, 0, delayMixer, 0);
AudioConnection          patchCord14(overdriveGainAmp, overdriveLevelAmp);
AudioConnection          patchCord15(delayAmp, delay1);
AudioConnection          patchCord16(delayMixer, 0, reverbMixer, 0);
AudioConnection          patchCord17(delayMixer, reverbAmp);
AudioConnection          patchCord18(delayMixer, delayAmp);
AudioConnection          patchCord19(delay1, 0, delayMixer, 1);
AudioConnection          patchCord20(reverbMixer, 0, masterMixer, 3);
AudioConnection          patchCord21(freeverb1, 0, reverbMixer, 1);
AudioConnection          patchCord22(reverbAmp, freeverb1);
AudioConnection          patchCord23(playSdWav1, 0, playSDMixer, 0);
AudioConnection          patchCord24(playSdWav1, 1, playSDMixer, 1);
AudioConnection          patchCord25(metronomeDrum, 0, masterMixer, 2);
AudioConnection          patchCord26(playSDMixer, 0, masterMixer, 1);
AudioConnection          patchCord27(masterMixer, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=190.66665649414062,470.99999237060547
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
Encoder enc(3, 2);
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

// BackingTrack global variables
std::vector<String> backingTrack_files;

float fuzzWaveshape[] = {-1.0, 1.0, -1.0};

// SD
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


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


  /* SD */
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    display.fillScreen(BLACK);
    display.drawBitmap(0, 0, noSDCard, 160, 80, WHITE);
    display.display();
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  

  /* Tuner */
  notefreqAmp.gain(0);
  notefreq1.begin(0.15);

  /* Effects */
  //Drive
  dc1.amplitude(0.1);
  waveshape1.shape(fuzzWaveshape, 3);
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

  /* BackingTrack*/
  File backingTrackDir = SD.open("backingtracks");
  while(1) {
    File entry = backingTrackDir.openNextFile();
    if(!entry) {
      break;
    }
    if(!entry.isDirectory()) {
      backingTrack_files.push_back(entry.name());
      Serial.println(entry.name());
    }
    entry.close();
  }

  AudioInterrupts();

  page0_setup();
}

int previousMemoryUsage = 0;

void loop() {
  //printAudioMemoryUsage();

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
