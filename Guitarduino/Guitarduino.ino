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
#include <vector>

// Audio
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=307.1999816894531,581.9999847412109
AudioEffectGranular      granular1;      //xy=435.1999816894531,1214.999984741211
AudioAmplifier           notefreqAmp;    //xy=489.1999816894531,291.99998474121094
AudioAmplifier           compressorAmp;  //xy=584.1999816894531,585.9999847412109
AudioAnalyzePeak         compressorPeak; //xy=597.1999816894531,655.9999847412109
AudioAnalyzeNoteFrequency notefreq1;      //xy=645.1999816894531,293.99998474121094
AudioAmplifier           compressorLevelAmp; //xy=790.1999816894531,585.9999847412109
AudioAnalyzePeak         peak2;          //xy=860.1999816894531,819.9999847412109
AudioAmplifier           distortionFirstAmp; //xy=1244.1999816894531,799.9999847412109
AudioEffectWaveshaper    distortionWaveshape; //xy=1247.1999816894531,843.9999847412109
AudioAmplifier           distortionLevelAmp; //xy=1250.1999816894531,883.9999847412109
AudioEffectWaveshaper    overdriveWaveshape; //xy=1252.1999816894531,674.9999847412109
AudioEffectWaveshaper    fuzzWaveShape;  //xy=1255.1999816894531,966.9999847412109
AudioAmplifier           overdriveLevelAmp; //xy=1257.1999816894531,715.9999847412109
AudioAmplifier           overdriveFirstAmp; //xy=1258.1999816894531,635.9999847412109
AudioMixer4              driveMixer;     //xy=1485.1999816894531,715.9999847412109
AudioFilterBiquad        driveBiquad;    //xy=1642.1999816894531,693.9999847412109
AudioMixer4              driveOnOffMixer; //xy=1849.1999816894531,597.9999847412109
AudioEffectFlange        chorusFlange;   //xy=2280.199981689453,651.9999847412109
AudioMixer4              chorusMixer;    //xy=2486.199981689453,624.9999847412109
AudioAmplifier           delayAmp;       //xy=2634.199981689453,764.9999847412109
AudioMixer4              delayMixer;     //xy=2691.199981689453,645.9999847412109
AudioEffectDelay         delay1;         //xy=2768.199981689453,764.9999847412109
AudioMixer4              reverbMixer;    //xy=3016.199981689453,644.9999847412109
AudioEffectFreeverb      freeverb1;      //xy=3016.199981689453,695.9999847412109
AudioAmplifier           reverbAmp;      //xy=3020.199981689453,733.9999847412109
AudioPlaySdWav           playSdWav1;     //xy=3040.199981689453,466.99998474121094
AudioSynthSimpleDrum     metronomeDrum;  //xy=3200.199981689453,570.9999847412109
AudioMixer4              playSDMixer;    //xy=3255.199981689453,476.99998474121094
AudioInputUSB            usb1;           //xy=3332.199981689453,345.99998474121094
AudioMixer4              usbMixer;       //xy=3500.199981689453,363.99998474121094
AudioMixer4              masterMixer;    //xy=3538.199981689453,617.9999847412109
AudioOutputI2S           i2s2;           //xy=3701.199981689453,611.9999847412109
AudioConnection          patchCord1(i2s1, 0, compressorAmp, 0);
AudioConnection          patchCord2(i2s1, 0, notefreqAmp, 0);
AudioConnection          patchCord3(i2s1, 0, compressorPeak, 0);
AudioConnection          patchCord4(notefreqAmp, notefreq1);
AudioConnection          patchCord5(compressorAmp, compressorLevelAmp);
AudioConnection          patchCord6(compressorLevelAmp, 0, driveOnOffMixer, 0);
AudioConnection          patchCord7(compressorLevelAmp, peak2);
AudioConnection          patchCord8(compressorLevelAmp, overdriveFirstAmp);
AudioConnection          patchCord9(compressorLevelAmp, fuzzWaveShape);
AudioConnection          patchCord10(compressorLevelAmp, distortionFirstAmp);
AudioConnection          patchCord11(distortionFirstAmp, distortionWaveshape);
AudioConnection          patchCord12(distortionWaveshape, distortionLevelAmp);
AudioConnection          patchCord13(distortionLevelAmp, 0, driveMixer, 1);
AudioConnection          patchCord14(overdriveWaveshape, overdriveLevelAmp);
AudioConnection          patchCord15(fuzzWaveShape, 0, driveMixer, 2);
AudioConnection          patchCord16(overdriveLevelAmp, 0, driveMixer, 0);
AudioConnection          patchCord17(overdriveFirstAmp, overdriveWaveshape);
AudioConnection          patchCord18(driveMixer, driveBiquad);
AudioConnection          patchCord19(driveBiquad, 0, driveOnOffMixer, 1);
AudioConnection          patchCord20(driveOnOffMixer, 0, chorusMixer, 0);
AudioConnection          patchCord21(driveOnOffMixer, chorusFlange);
AudioConnection          patchCord22(chorusFlange, 0, chorusMixer, 1);
AudioConnection          patchCord23(chorusMixer, 0, delayMixer, 0);
AudioConnection          patchCord24(delayAmp, delay1);
AudioConnection          patchCord25(delayMixer, 0, reverbMixer, 0);
AudioConnection          patchCord26(delayMixer, reverbAmp);
AudioConnection          patchCord27(delayMixer, delayAmp);
AudioConnection          patchCord28(delay1, 0, delayMixer, 1);
AudioConnection          patchCord29(reverbMixer, 0, masterMixer, 3);
AudioConnection          patchCord30(freeverb1, 0, reverbMixer, 1);
AudioConnection          patchCord31(reverbAmp, freeverb1);
AudioConnection          patchCord32(playSdWav1, 0, playSDMixer, 0);
AudioConnection          patchCord33(playSdWav1, 1, playSDMixer, 1);
AudioConnection          patchCord34(metronomeDrum, 0, masterMixer, 2);
AudioConnection          patchCord35(playSDMixer, 0, masterMixer, 1);
AudioConnection          patchCord36(usb1, 0, usbMixer, 0);
AudioConnection          patchCord37(usb1, 1, usbMixer, 1);
AudioConnection          patchCord38(usbMixer, 0, masterMixer, 0);
AudioConnection          patchCord39(masterMixer, 0, i2s2, 0);
AudioConnection          patchCord40(masterMixer, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=266.1999816894531,479.99998474121094
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
const uint16_t BOOT = 0x0617;

// Encoder
Encoder enc(3, 2);
long oldPosition = 0;

const int buttonPin = 1;
Bounce bounce = Bounce();


// Count pages from 0
int currentPage = 0;
int pageCount = 4;
bool pageSelected = false;

// Compressor
bool ef_compressor_on = false;
int ef_compressor_level = 0;
int ef_compressor_threshold = 10;
int ef_compressor_release = 0;
const float ef_compressor_thresholdMax = 0.5;  //Adjust if needed (use compressorPeak.read() to find the right value)
const float ef_compressor_ratio = 0.125;

// Chorus
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short delayline[CHORUS_DELAY_LENGTH];

// Metronome global variables
bool metronome_on = false;
float metronome_previousMillis;
int metronome_bpm = 100;
int metronome_beatsPerBar = 4;
int metronome_currentBeat = 0;

// BackingTrack global variables
std::vector<String> backingTrack_files;

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
  display.initR(INITR_MINI160x80_PLUGIN);
  display.setRotation(3);
  display.invertDisplay(false);
  display.drawBitmap(0, 0, Boot, 160, 80, BOOT);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(62, 47);
  display.print("Ver:Development");
  display.display();
  delay(2000);


  /* Audio */
  AudioMemory(1000);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.lineInLevel(10);
  sgtl5000_1.volume(1);
  //sgtl5000_1.adcHighPassFilterDisable();

  masterMixer.gain(0, 1);
  masterMixer.gain(1, 1);
  masterMixer.gain(2, 0);
  masterMixer.gain(3, 0.5);


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
  //Dynamic
  compressorAmp.gain(1);
  compressorLevelAmp.gain(1);

  //Drive
  disableDrive();

  //Chorus
  chorusFlange.begin(delayline, CHORUS_DELAY_LENGTH, 0, 0, 0);
  chorusMixer.gain(0, 1);
  chorusMixer.gain(1, 0);

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
  printAudioMemoryUsage();
  float requestedVolume = usb1.volume();
  usbMixer.gain(0, requestedVolume);
  usbMixer.gain(1, requestedVolume);
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

  // Compressor
  if (compressorPeak.available() && ef_compressor_on) {
    float peak = compressorPeak.read();
    float threshold =  ef_compressor_thresholdMax * (float(ef_compressor_threshold) / 10);
    float reduction;
    if(peak > threshold) {
      reduction = ((peak - threshold) * ef_compressor_ratio + threshold) / peak;
      
      compressorAmp.gain(reduction);
      compressorAmp.gain(reduction);  
      Serial.println("Peak: " + String(peak) + " Threshold: " + String(threshold) + " Gain: " + String(reduction) + " NewPeak: " + String(peak2.read()));

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
