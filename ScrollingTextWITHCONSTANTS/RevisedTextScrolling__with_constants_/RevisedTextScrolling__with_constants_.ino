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
//This is the starting point of our function, the x which is changing
int xStartingPoint; 
const int firstFourWidth = 4;
const int offsetSecondFour = 8;
const int secondFourWidth = 4;
const int offsetSix = 16;
const int sixWidth = 4;
const int offsetOne = 24;
const int valueTopY = 2;
const int ValueMidY = 8;
const int ValueBottomY = 13;

//Forward declaration
void drawFour1 ();
void drawFour2 ();
void drawSix ();
void drawOne ();
void drawBarriers ();

//Starts the coordinates of our function at these values when we restart
void restart() {
  FastLED.clear();
  xStartingPoint = 15;
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
  if (xStartingPoint+offsetOne < 0) {
    restart();
  }
  FastLED.clear(true);

  xStartingPoint--;

  drawFirstFour ();
  drawSecondFour ();
  drawSix ();
  drawOne ();
  drawBarriers ();

  FastLED.show();
  FastLED.delay(100);

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
void drawFirstFour () {
  //draws "4"
  //This is the first vertical line segment (short) of the four
  leds.DrawLine(xStartingPoint, 2, xStartingPoint, 8, CRGB:: White);
  //This is the middle horizontal section of the four
  leds.DrawLine(xStartingPoint, 8, xStartingPoint+firstFourWidth, 8, CRGB:: White);
  //This is the long vertical section (backbone) of the four
  leds.DrawLine(xStartingPoint+firstFourWidth, 2,xStartingPoint+firstFourWidth, 13, CRGB:: White);
}

void drawSecondFour () {
  //draws "4"
  leds.DrawLine(xStartingPoint+offsetSecondFour, 2, xStartingPoint+offsetSecondFour, 8, CRGB:: Blue);
  leds.DrawLine(xStartingPoint+offsetSecondFour, 8, xStartingPoint+offsetSecondFour+secondFourWidth, 8, CRGB:: Blue);
  leds.DrawLine(xStartingPoint+offsetSecondFour+secondFourWidth, 2, xStartingPoint+offsetSecondFour+secondFourWidth, 13, CRGB:: Blue);
}

void drawSix () {
  //draws "6"
  leds.DrawLine(xStartingPoint+offsetSix, 2, xStartingPoint+offsetSix+sixWidth, 2, CRGB:: White);
  leds.DrawLine(xStartingPoint+offsetSix, 2, xStartingPoint+offsetSix, 13, CRGB:: White);
  leds.DrawLine(xStartingPoint+offsetSix, 8, xStartingPoint+offsetSix+sixWidth, 8, CRGB:: White);
  leds.DrawLine(xStartingPoint+offsetSix, 13, xStartingPoint+offsetSix+sixWidth, 13, CRGB:: White);
  leds.DrawLine(xStartingPoint+offsetSix+sixWidth, 8, xStartingPoint+offsetSix+sixWidth, 13, CRGB:: White);
}

void drawOne () {
  //draws "1"
  leds.DrawLine(xStartingPoint+offsetOne, 2,xStartingPoint+offsetOne, 13, CRGB:: Blue);
}

void drawBarriers () {
  leds.DrawLine(15, 0, 15, 15, CRGB:: Green);
  leds.DrawLine(0, 0, 0, 15, CRGB:: Green);
}
