#include <Adafruit_GFX_Buffer.h>

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <Encoder.h>

#define TFT_CS  4
#define TFT_RST 9
#define TFT_DC 5

Encoder enc(2, 3);
long oldPosition  = -999;


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

// Count pages from 0
int currentPage = 0;
int pageCount = 4;
int menuLevel = 0;


void setup() {
  Serial.begin(9600);
  page0_setup();
}

void loop() {
  switch(currentPage) {
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
}

long readEncoder() {
  long newPosition = round(enc.read() / 4);
  if (newPosition - oldPosition > 0) {
    oldPosition = newPosition;
    return(1);
  }
  else if (newPosition - oldPosition < 0) {
    oldPosition = newPosition;
    return(-1);
  }
  return(0);
}
