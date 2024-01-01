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
AudioInputI2S            i2s1;           //xy=201.1999969482422,813.1999969482422
AudioAnalyzeNoteFrequency notefreq1;      //xy=460.2000274658203,810.2000231742859
AudioOutputI2S           i2s2;           //xy=460.20002365112305,912.200023651123
AudioConnection          patchCord1(i2s1, 1, i2s2, 1);
AudioConnection          patchCord2(i2s1, 1, notefreq1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=128.1999969482422,951.1999969482422
// GUItool: end automatically generated code







// Display
#define CS 4
#define DC 5
#define RST 9

//Adafruit_ST7735 display = Adafruit_ST7735(CS, DC, RST);
Adafruit_GFX_Buffer<Adafruit_ST7735> display = Adafruit_GFX_Buffer<Adafruit_ST7735>(80, 160, Adafruit_ST7735(&SPI, CS, DC, RST));

const uint16_t BLACK = 0x0000;
const uint16_t WHITE = 0xffff;
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
int menuLevel = 0;

void setup() {
  AudioNoInterrupts();

  // System
  Serial.begin(9600);
  pinMode(1, INPUT_PULLUP);

  // Display
  display.initR(INITR_MINI160x80);
  display.setRotation(3);
  display.invertDisplay(true);

  // Audio
  AudioMemory(50);
  
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(1);

  notefreq1.begin(0.15);

  AudioInterrupts();

  page0_setup();
}

void loop() {
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

  if (menuLevel == 0) {
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
