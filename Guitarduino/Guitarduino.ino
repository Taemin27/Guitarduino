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
AudioInputI2S            i2s1;           //xy=254.66665649414062,447.99999237060547
AudioAmplifier           notefreqAmp;    //xy=443.6666717529297,174.00000953674316
AudioAnalyzeNoteFrequency notefreq1;      //xy=599.6666717529297,176.00000953674316
AudioAmplifier           compressorAmp;           //xy=601.6667022705078,464.66676235198975
AudioAnalyzePeak         compressorPeak;          //xy=614.6666946411133,534.6667499542236
AudioAmplifier           compressorLevelAmp;           //xy=807.6667709350586,464.66676235198975
AudioAnalyzePeak         peak2;          //xy=877.8062591552734,698.8250045776367
AudioSynthWaveformDc     dc1;            //xy=1120.6667823791504,531.0000152587891
AudioEffectWaveshaper    waveshape1;     //xy=1134.6667823791504,489.00001335144043
AudioEffectWaveFolder    wavefolder1;    //xy=1318.666790008545,516.0000133514404
AudioMixer4              overdriveMixer; //xy=1321.6667709350586,462.00001335144043
AudioAmplifier           distortionLevelAmp; //xy=1322.666790008545,592.0000133514404
AudioFilterBiquad        overdriveBiquad; //xy=1323.666790008545,554.0000133514404
AudioAmplifier           distortionGainAmp; //xy=1324.666790008545,631.0000133514404
AudioAmplifier           overdriveLevelAmp; //xy=1324.666790008545,674.0000133514404
AudioAmplifier           overdriveGainAmp; //xy=1328.666790008545,714.0000133514404
AudioAmplifier           delayAmp;       //xy=1553.666790008545,616.0000133514404
AudioMixer4              delayMixer;     //xy=1637.666790008545,482.00001335144043
AudioEffectDelay         delay1;         //xy=1844.666790008545,654.0000133514404
AudioMixer4              reverbMixer;    //xy=1962.666790008545,481.00001335144043
AudioEffectFreeverb      freeverb1;      //xy=1962.666790008545,532.0000133514404
AudioAmplifier           reverbAmp;      //xy=1966.666790008545,570.0000133514404
AudioPlaySdWav           playSdWav1;     //xy=1986.6666870117188,303.99999809265137
AudioSynthSimpleDrum     metronomeDrum;  //xy=2146.6666870117188,407.99999809265137
AudioMixer4              playSDMixer;    //xy=2201.6666870117188,313.99999809265137
AudioMixer4              masterMixer;    //xy=2484.6666870117188,454.99999809265137
AudioOutputI2S           i2s2;           //xy=2647.6666870117188,448.99999809265137
AudioConnection          patchCord1(i2s1, 0, notefreqAmp, 0);
AudioConnection          patchCord2(i2s1, 0, compressorAmp, 0);
AudioConnection          patchCord3(i2s1, 0, compressorPeak, 0);
AudioConnection          patchCord4(notefreqAmp, notefreq1);
AudioConnection          patchCord5(compressorAmp, compressorLevelAmp);
AudioConnection          patchCord6(compressorLevelAmp, waveshape1);
AudioConnection          patchCord7(compressorLevelAmp, 0, overdriveMixer, 0);
AudioConnection          patchCord8(compressorLevelAmp, overdriveGainAmp);
AudioConnection          patchCord9(compressorLevelAmp, peak2);
AudioConnection          patchCord10(dc1, 0, wavefolder1, 1);
AudioConnection          patchCord11(waveshape1, 0, overdriveMixer, 2);
AudioConnection          patchCord12(wavefolder1, 0, overdriveMixer, 1);
AudioConnection          patchCord13(overdriveMixer, 0, delayMixer, 0);
AudioConnection          patchCord14(distortionLevelAmp, overdriveBiquad);
AudioConnection          patchCord15(overdriveBiquad, 0, wavefolder1, 0);
AudioConnection          patchCord16(distortionGainAmp, distortionLevelAmp);
AudioConnection          patchCord17(overdriveLevelAmp, distortionGainAmp);
AudioConnection          patchCord18(overdriveGainAmp, overdriveLevelAmp);
AudioConnection          patchCord19(delayAmp, delay1);
AudioConnection          patchCord20(delayMixer, 0, reverbMixer, 0);
AudioConnection          patchCord21(delayMixer, reverbAmp);
AudioConnection          patchCord22(delayMixer, delayAmp);
AudioConnection          patchCord23(delay1, 0, delayMixer, 1);
AudioConnection          patchCord24(reverbMixer, 0, masterMixer, 3);
AudioConnection          patchCord25(freeverb1, 0, reverbMixer, 1);
AudioConnection          patchCord26(reverbAmp, freeverb1);
AudioConnection          patchCord27(playSdWav1, 0, playSDMixer, 0);
AudioConnection          patchCord28(playSdWav1, 1, playSDMixer, 1);
AudioConnection          patchCord29(metronomeDrum, 0, masterMixer, 2);
AudioConnection          patchCord30(playSDMixer, 0, masterMixer, 1);
AudioConnection          patchCord31(masterMixer, 0, i2s2, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=220.66665649414062,362.99999237060547
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

// Compressor global variables
bool ef_compressor_on = false;
int ef_compressor_level = 0;
int ef_compressor_threshold = 10;
int ef_compressor_release = 0;
float ef_compressor_maxRelease = 0;
float ef_compressor_releaseMillis = 0;
float ef_compressor_previousMillis = 0; 
float ef_compressor_previousPeak = 0;
const float ef_compressor_thresholdMax = 0.35;  //Adjust if needed (use compressorPeak.read() to find the right value)
const float ef_compressor_ratio = 0.125;


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
  display.drawBitmap(0, 0, Boot, 160, 80, BOOT);
  display.display();
  delay(1000);


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
  //Dynamic
  compressorAmp.gain(1);
  compressorLevelAmp.gain(1);

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

  // Compressor
  if(ef_compressor_on) {
    float reduction = 1;
    if (compressorPeak.available()) {
      float peak = compressorPeak.read();
      //Serial.println(ef_compressor_thresholdMax * (float(ef_compressor_threshold) / 10));
      float threshold =  ef_compressor_thresholdMax * (float(ef_compressor_threshold) / 10);
      if(peak > threshold) {
        reduction = ((peak - threshold) * ef_compressor_ratio + threshold) / peak;

        if(peak > ef_compressor_previousPeak) {
          ef_compressor_releaseMillis = ef_compressor_maxRelease;
        }

        if(ef_compressor_releaseMillis > 0) {
          float currentMillis = millis();
          if(currentMillis - ef_compressor_previousMillis >= 10) {
            ef_compressor_releaseMillis += currentMillis - ef_compressor_previousMillis;
            if(ef_compressor_releaseMillis > ef_compressor_maxRelease) {
              ef_compressor_releaseMillis = ef_compressor_maxRelease;
            }
            reduction = reduction + (1 - reduction) * (ef_compressor_releaseMillis / ef_compressor_maxRelease);
            ef_compressor_previousMillis = currentMillis;
          }
        }
        compressorAmp.gain(reduction);
        
        Serial.println("Peak: " + String(peak) + " Threshold: " + String(threshold) + " Gain: " + String(reduction) + " NewPeak: " + String(peak2.read()));

      }
    }
    compressorAmp.gain(reduction);  
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
