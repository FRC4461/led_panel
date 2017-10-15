// This uses:
//    FastLED from http://fastled.io

#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET    WS2811

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16
#define NUM_LEDS 256

#define BRIGHTNESS  16
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 16

extern const unsigned char Smile[256 / 8];

int counter;


// This maps an X and Y coordinate to the specific LED index.
// Note that the coordinate system starts with 0, 0 in the upper-left.
int index(int x, int y)
{
    if (y % 2)
        return((y * MATRIX_WIDTH) + x);
    else
        return((((y + 1) * MATRIX_WIDTH) - 1) - x);
}


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);

    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    // Show the smile for 256 ticks before showing test pattern.
    counter = -256;
    FastLED.show();
}


void renderBitmapFromProgmem(const unsigned char* bitmap)
{
    // Render the black and white bitmap in a color.
    for(int i = 0; i < NUM_LEDS; i++) {
        int position = index(i % MATRIX_WIDTH, i / MATRIX_WIDTH);
        // Since this is progmem we must read it differently.
        byte imageData = pgm_read_byte_near(bitmap + (i/8));
        // This logic gets the single bit from the byte for this pixel.
        // Note that the bits are in order, so we need to get the left most bit for the first
        // pixel. To get this bit we shift right 7 times, 6 times for the next bit and so on
        // until we get to the next byte.
        leds[position] = ((imageData >> (7 - (i % 8))) & 0x01) == 0 ? CRGB::Black : CRGB::Orange;
    }
}


void showSmile()
{
    renderBitmapFromProgmem(Smile);
}


void loop()
{
    if (counter >= 0 && counter < 256) {
        leds[index(counter % MATRIX_WIDTH, counter / MATRIX_WIDTH)] = CRGB::Orange;
        counter++;
    } else {
        showSmile();
    }
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

// This is a Smile emoji that will live in the more plentiful program memory.
const unsigned char Smile[] PROGMEM =
{
    // Converted using https://manytools.org/hacker-tools/image-to-byte-array
    0x3, 0xc0, 0x8, 0x10, 0x20, 0x4, 0x0, 0x0, 0x40, 0x2, 0xc, 0x30, 0x8a, 0x71, 0x88, 
    0x11, 0x80, 0x1, 0x80, 0x1, 0x8, 0x10, 0x48, 0x12, 0x7, 0xE0, 0x20, 0x4, 0x8, 0x10, 
    0x3, 0xc0,
};
