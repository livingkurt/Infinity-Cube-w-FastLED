#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    144
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
#define STROBE 5
#define GAP 1
#define COLOR_CHANGE_RATE 0
CRGB leds[NUM_LEDS];

//int a = 1;
//int b = 2;
//int c = 3;
int h = 0;


void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int i = 0; i < 10; i++) {
      leds[random(NUM_LEDS)] = CHSV( 255, 0, random(0, 255) ); // Change To Random LED and change color to White
      delay(STROBE);
        FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CHSV( 0, 0, 0 )); // Set all to Off.
    FastLED.show();
    delay(GAP);
  }

}
