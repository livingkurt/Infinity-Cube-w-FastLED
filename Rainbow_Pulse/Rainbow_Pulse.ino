#include <FastLED.h>
#define LED_PIN 5
#define NUM_LEDS 144
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define RATE 10
#define GAP 10
#define NUM_X 12

CRGB leds[NUM_LEDS];

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 120

int start_hue;
int delta_hue = 10;

int ROW = NUM_LEDS / NUM_X;

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  Serial.begin(9600);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  start_hue = -1 * millis() / RATE;
  for (int i = 0; i < ROW; i++)
  {
    // Row 1
    leds[ROW - 1 - i] = CHSV(start_hue, 255, 255);
    // Row 2
    leds[ROW + i] = CHSV(start_hue, 255, 255);
    // Row 3
    leds[i + (ROW * 2)] = CHSV(start_hue, 255, 255);
    // Row 4
    leds[ROW * 4 - 1 - i] = CHSV(start_hue, 255, 255);
    // Row 5
    leds[ROW * 5 - 1 - i] = CHSV(start_hue, 255, 255);
    // Row 6
    leds[ROW * 5 + i] = CHSV(start_hue, 255, 255);
    // Row 7
    leds[i + ROW * 6] = CHSV(start_hue, 255, 255);
    // Row 8
    leds[ROW * 8 - 1 - i] = CHSV(start_hue, 255, 255);
    // Row 9
    leds[i + ROW * 8] = CHSV(start_hue, 255, 255);
    // Row 10
    leds[ROW * 10 - 1 - i] = CHSV(start_hue, 255, 255);
    // Row 11
    leds[i + ROW * 10] = CHSV(start_hue, 255, 255);
    // Row 12
    leds[NUM_LEDS - 1 - i] = CHSV(start_hue, 255, 255);

    start_hue += delta_hue;
    FastLED.show();
  };
}