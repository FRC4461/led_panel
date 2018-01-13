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
#define BRIGHTNESS          20


// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

void setup() {
  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.showColor(CRGB::Blue);
  Serial.begin(115200);
  FastLED.clear(true);
}

void loop() {
  int16_t sx, sy, x, y, xc, yc, r;
  uint8_t h;
  int incomingByte;
  int b, d;
  for (x = 0; x < leds.Size(); x++)
  {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      if (incomingByte == 'b') {
        b = Serial.parseInt();
        Serial.println(b);
        FastLED.setBrightness(b);
        FastLED.show();
      }
      else if (incomingByte == 'm') {
        FastLED.clear(true);
        drawMushroom();
        FastLED.show();
      }
      else if (incomingByte == 'n') {
        FastLED.clear(true);
        drawFace();
        FastLED.show();
      }
      else if (incomingByte == 'd') {
        int x = Serial.parseInt();
        int y = Serial.parseInt();
        int r = Serial.parseInt();
        int g = Serial.parseInt();
        int b = Serial.parseInt();
        leds.DrawLine(x, y, x, y, CRGB(r, g, b));
        FastLED.show();
      }
      else if (incomingByte == 'c') {
        FastLED.clear(true);
        FastLED.show();
      }
      else if (incomingByte == 'h') {
        Serial.println(" b <brightness> - changes brightness ");
        Serial.println(" m - draws Mushroom ");
        Serial.println(" c - clears panel ");
        Serial.println(" n - draws face ");
        Serial.println(" d <x,y,r,g,b> - makes LED ");
      }
    }
  }
}

void drawMushroom() {
  //Draw Red head
  leds.DrawFilledCircle(8, 6, 7, CRGB(200, 0, 0));
  //Draw white circle thing
  leds.DrawFilledCircle(8, 5, leds.Width() / 4, CRGB(100, 100, 100));
  //DrawFace outline
  leds.DrawFilledRectangle(5 , 12, 11, 15, CRGB(250, 160, 110));
  //Draw Eyes
  leds.DrawLine(7, 13, 7, 14, CRGB::Black);
  leds.DrawLine(9, 13, 9, 14, CRGB::Black);
  //Draw White part in helmet
  leds.DrawLine(1, 4, 1, 8, CRGB::White);
  leds.DrawLine(2, 2, 2, 10, CRGB::White);
  leds.DrawLine(15, 4, 15, 8, CRGB::White);
  leds.DrawLine(14, 2, 14, 10, CRGB::White);
}

void drawFace() {
  int16_t x = leds.Width() / 2;
  int16_t y = leds.Height() / 2;
  leds.DrawCircle(x, y, 6, CRGB::Purple);
  leds.DrawCircle(5, 6, 1, CRGB::Blue);
  leds.DrawCircle(10, 6, 1, CRGB::Blue);
  leds.DrawRectangle(5, 10, 11, 11, CRGB::Green);
}

//Function to draw triangles
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, CRGB color) {
  leds.DrawLine(x0, y0, x1, y1, color);
  leds.DrawLine(x1, y1, x2, y2, color);
  leds.DrawLine(x2, y2, x0, y0, color);
}

//Function to draw custom quadrilaterals
void drawQuadrilateral(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, CRGB color) {
  leds.DrawLine(x0, y0, x1, y1, color);
  leds.DrawLine(x1, y1, x2, y2, color);
  leds.DrawLine(x2, y2, x3, y3, color);
  leds.DrawLine(x3, y3, x0, y0, color);
}

void drawNotObject () {
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 8, CRGB:: Pink);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 7, CRGB:: Blue);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 6, CRGB:: Orange);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 5, CRGB:: Red);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 4, CRGB:: Pink);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 3, CRGB:: Blue);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 2, CRGB:: Orange);
  leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, 1, CRGB:: Red);
}

void drawTeamLogo () {
  leds.DrawLine(0, 0, 0, 7, CRGB:: White);
  leds.DrawLine(0, 7, 3, 7, CRGB:: White);
  leds.DrawLine(3, 0, 3, 15, CRGB:: White);
  leds.DrawLine(5, 0, 0, 7, CRGB:: Black);
  leds.DrawLine(5, 7, 8, 7, CRGB:: Black);
  leds.DrawLine(8, 0, 8, 15, CRGB:: Black);
}
