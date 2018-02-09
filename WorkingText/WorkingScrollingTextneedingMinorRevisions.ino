#include <FastLED.h>
#include <LEDMatrix.h>
#include <FastLED_GFX.h>

// Change the next defines to match your matrix type and size
#define DATA_PIN            5

#define COLOR_ORDER         GRB
#define CHIPSET             WS2811

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        16
#define MATRIX_HEIGHT       16
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE
#define BRIGHTNESS          5

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
bool teamLogo;
int xOne1;
int timeToRestartTheScroll = xOne1;
int xFour1;
int xFour2;
int xSix1;
int xSix2;
int xOtherFour1;
int xOtherFour2;

//Forward declaration
void drawFour1 ();
void drawFour2 ();
void drawSix ();
void drawOne ();
void drawBarriers ();

//Starts the coordinates of our function at these values when we restart
void restart() {
  FastLED.clear();
  timeToRestartTheScroll = xOne1;
  xFour1 = 15;
  xFour2 = xFour1 + 2;
  xOtherFour1 = xFour1 + 4;
  xOtherFour2 = xFour1 + 6;
  xSix1 = xFour1 + 8;
  xSix2 = xFour1 + 10;
  xOne1 = xFour1 + 12;
}
void setup() {
  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.showColor(CRGB::Black);
  Serial.begin(115200);
  restart();
}

void loop() {
  int incomingByte;
  int b;
  //if (Serial.available() > 0) {
  // read the incoming byte:
  //incomingByte = Serial.read();
  //if (incomingByte == 'l') {
  if (xOne1 < 0) {
    restart();
  }
  FastLED.clear(true);

  xFour1--;
  xFour2 = xFour1 + 2;
  xOtherFour1 = xFour1 + 4;
  xOtherFour2 = xFour1 + 6;
  xSix1 = xFour1 + 8;
  xSix2 = xFour1 + 10;
  xOne1 = xFour1 + 12;

  drawFour1 ();
  drawFour2 ();
  drawSix ();
  drawOne ();
  drawBarriers ();

  FastLED.show();
  FastLED.delay(50);

  if (incomingByte == 'b') {
    b = Serial.parseInt();
    Serial.println(b);
    FastLED.setBrightness(b);
    FastLED.show();
  }
  else if (incomingByte == 'c') {
    restart();
  }
  else if (incomingByte == 'h') {
    Serial.println(" b <brightness> - changes brightness ");
    Serial.println(" l - draws BROKEN team logo ");
    Serial.println(" c - clears panel ");
    Serial.println(" d <x,y,r,g,b> - makes LED ");
  }
}

//draws "4461"
void drawFour1 () {
  //draws "4"
  leds.DrawLine(xFour1, 2, xFour1, 8, CRGB:: White);
  leds.DrawLine(xFour1, 8, xFour2, 8, CRGB:: White);
  leds.DrawLine(xFour2, 2, xFour2, 13, CRGB:: White);
}

void drawFour2 () {
  //draws "4"
  leds.DrawLine(xOtherFour1, 2, xOtherFour1, 8, CRGB:: Blue);
  leds.DrawLine(xOtherFour1, 8, xOtherFour2, 8, CRGB:: Blue);
  leds.DrawLine(xOtherFour2, 2, xOtherFour2, 13, CRGB:: Blue);
}

void drawSix () {
  //draws "6"
  leds.DrawLine(xSix1, 2, xSix2, 2, CRGB:: White);
  leds.DrawLine(xSix1, 2, xSix1, 13, CRGB:: White);
  leds.DrawLine(xSix1, 8, xSix2, 8, CRGB:: White);
  leds.DrawLine(xSix1, 13, xSix2, 13, CRGB:: White);
  leds.DrawLine(xSix2, 8, xSix2, 13, CRGB:: White);
}

void drawOne () {
  //draws "1"
  leds.DrawLine(xOne1, 2, xOne1, 13, CRGB:: Blue);
}

void drawBarriers () {
  leds.DrawLine(15, 0, 15, 15, CRGB:: Purple);
  leds.DrawLine(0, 0, 0, 15, CRGB:: Purple);
}

