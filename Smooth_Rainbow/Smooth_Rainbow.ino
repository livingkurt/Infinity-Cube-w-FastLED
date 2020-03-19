#include <FastLED.h>
#define LED_PIN 5
#define NUM_LEDS 144
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define RATE 10
#define GAP 10
CRGB leds[NUM_LEDS];

int start_hue;
int delta_hue = 20;
int h = 0;
int j = 0;

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  Serial.begin(9600);
  // FastLED.clear();
  // FastLED.show();
}

void loop()
{

  start_hue = -1 * millis() / RATE;
  for (int i = 0; i < NUM_LEDS; i++)

  {
    leds[i] = CHSV(start_hue, 255, 255);
    start_hue += delta_hue;
  };
  FastLED.show();
}