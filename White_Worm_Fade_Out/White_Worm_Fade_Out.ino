#include <FastLED.h>
#define LED_PIN 5
#define NUM_LEDS 144
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define STROBE 30
#define RATE 10
#define GAP 10
CRGB leds[NUM_LEDS];

int start_hue;
int delta_hue;

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  Serial.begin(9600);

}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++) {

    //    int pos = beatsin16(10,0,NUM_LEDS);
    leds[i] += CHSV( 255, 0, 255);

    FastLED.show();
    delay(STROBE);
    fadeToBlackBy( leds, NUM_LEDS, 30);
    FastLED.show();
  }



}
