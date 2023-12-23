#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <Encoder.h>


String pages[] = { "Tuner", "effects", "metronome", "backingTrack", "record" };

#define TFT_CS  4
#define TFT_RST 9
#define TFT_DC 5


// Encoder
#define outputA 2
#define outputB 3
int aState;
int aLastState;


void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);
}

void loop() {

}

