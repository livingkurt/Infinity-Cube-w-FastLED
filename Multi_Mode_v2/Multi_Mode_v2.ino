#include <FastLED.h>
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN 5
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define NUM_LEDS 144

CRGB leds[NUM_LEDS];

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 120

void setup()
{
  delay(3000); // 3 second delay for recovery
  Serial.begin(9600);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbow_cycle, sparkle_white, worm_fade_white, rainbow_pulse, sparkle_rainbow, worm_fade_rainbow, corner_to_corner_rainbow, all_fade, shooting_stars};
// SimplePatternList gPatterns = {rainbow_cycle};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS(20)
  {
    gHue++; // slowly cycle the "base color" through the rainbow
  }
  EVERY_N_SECONDS(10)
  {
    nextPattern(); // change patterns periodically
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

// Pattern 1
#define GAP_1 1
#define RATE 10
int start_hue_1;
int delta_hue_1 = 20;

void rainbow_cycle()
{
  Serial.println("pattern_1");
  start_hue_1 = -1 * millis() / RATE;
  for (int i = 0; i < NUM_LEDS; i++)

  {
    leds[i] = CHSV(start_hue_1, 255, 255);
    start_hue_1 += delta_hue_1;
  };
  FastLED.show();
}

// Pattern 2
#define STROBE_2 0.5
#define GAP_2 1

void sparkle_white()
{
  Serial.println("pattern_2");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    for (int i = 0; i < 10; i++)
    {
      leds[random(NUM_LEDS)] = CHSV(255, 0, random(0, 255)); // Change To Random LED and change color to White
      delay(STROBE_2);
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0)); // Set all to Off.
    FastLED.show();
    delay(GAP_2);
  }
}

// Pattern 3
#define GAP_3 1
#define STROBE_3 30

void worm_fade_white()
{
  Serial.println("pattern_3");
  for (int i = 0; i < NUM_LEDS; i++)
  {

    //    int pos = beatsin16(10,0,NUM_LEDS);
    leds[i] += CHSV(255, 0, 255);
    //    leds[i + 72] += CHSV( 255, 0, 255);

    FastLED.show();
    delay(STROBE_3);
    fadeToBlackBy(leds, NUM_LEDS, 30);
    FastLED.show();
  }
}

// Pattern 4

#define RATE_4 10
#define GAP_4 10
#define NUM_X_4 12
int start_hue_4;
int delta_hue_4 = 10;
int ROW_4 = NUM_LEDS / NUM_X_4;

void rainbow_pulse()
{
  Serial.println("pattern_4");
  start_hue_4 = -1 * millis() / RATE;
  for (int i = 0; i < ROW_4; i++)
  {
    // Row 1
    leds[ROW_4 - 1 - i] = CHSV(start_hue_4, 255, 255);
    // Row 2
    leds[ROW_4 + i] = CHSV(start_hue_4, 255, 255);
    // Row 3_4
    leds[i + (ROW_4 * 2)] = CHSV(start_hue_4, 255, 255);
    // Row 4
    leds[ROW_4 * 4 - 1 - i] = CHSV(start_hue_4, 255, 255);
    // Row 5
    leds[ROW_4 * 5 - 1 - i] = CHSV(start_hue_4, 255, 255);
    // Row 6
    leds[ROW_4 * 5 + i] = CHSV(start_hue_4, 255, 255);
    // Row 7
    leds[i + ROW_4 * 6] = CHSV(start_hue_4, 255, 255);
    // Row 8
    leds[ROW_4 * 8 - 1 - i] = CHSV(start_hue_4, 255, 255);
    // Row 9
    leds[i + ROW_4 * 8] = CHSV(start_hue_4, 255, 255);
    // Row 10
    leds[ROW_4 * 10 - 1 - i] = CHSV(start_hue_4, 255, 255);
    // Row 11
    leds[i + ROW_4 * 10] = CHSV(start_hue_4, 255, 255);
    // Row 12
    leds[NUM_LEDS - 1 - i] = CHSV(start_hue_4, 255, 255);

    start_hue_4 += delta_hue_4;
    FastLED.show();
  };
}

// Pattern 5
#define STROBE_5 0.5
#define GAP_5 0

void sparkle_rainbow()
{
  Serial.println("pattern_5");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    for (int i = 0; i < 10; i++)
    {
      leds[random(NUM_LEDS)] = CHSV(random(0, 255), 255, random(0, 255)); // Change To Random LED and change color to White
      delay(STROBE_5);
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0)); // Set all to Off.
    FastLED.show();
    delay(GAP_5);
  }
}

// Pattern 6
#define STROBE_6 30
#define RATE_6 10
#define GAP_6 10
int start_hue_6;
int delta_hue_6 = 20;

void worm_fade_rainbow()
{
  Serial.println("pattern_6");
  start_hue_6 = -1 * millis() / RATE_6;
  for (int i = 0; i < NUM_LEDS; i++)

  {
    leds[i] = CHSV(start_hue_6, 255, 255);
    start_hue_6 += delta_hue_6;
    FastLED.show();
    delay(STROBE_6);
    fadeToBlackBy(leds, NUM_LEDS, 30);
    FastLED.show();
  };
}

#define RATE_7 10
#define STROBE_7 100
#define GAP_7 10
#define NUM_X_7 12
int start_hue_7;
int delta_hue_7 = 20;
int ROW_7 = NUM_LEDS / 3;

void corner_to_corner_white()
{
  Serial.println("pattern_7");
  start_hue_7 = -1 * millis() / RATE;
  for (int i = 0; i < ROW_7; i++)
  {
    // Row 1
    leds[i] = CHSV(start_hue_7, 0, 255);
    // Row 2
    leds[ROW_7 + i] = CHSV(start_hue_7, 0, 255);
    // Row 3
    leds[i + (ROW_7 * 2)] = CHSV(start_hue_7, 0, 255);
    // Row 4
    leds[ROW_7 * 4 - 1 - i] = CHSV(start_hue_7, 0, 255);
    // Row 5
    leds[ROW_7 * 5 - 1 - i] = CHSV(start_hue_7, 0, 255);
    // Row 6
    leds[ROW_7 * 5 + i] = CHSV(start_hue_7, 0, 255);
    // Row 7
    leds[i + ROW_7 * 6] = CHSV(start_hue_7, 0, 255);
    // Row 8
    leds[ROW_7 * 8 - 1 - i] = CHSV(start_hue_7, 0, 255);
    // Row 9
    leds[i + ROW_7 * 8] = CHSV(start_hue_7, 0, 255);
    // Row 10
    leds[ROW_7 * 10 - 1 - i] = CHSV(start_hue_7, 0, 255);
    // Row 11
    leds[i + ROW_7 * 10] = CHSV(start_hue_7, 0, 255);
    // Row 12
    leds[NUM_LEDS - 1 - i] = CHSV(start_hue_7, 0, 255);

    start_hue_7 += delta_hue_7;
    FastLED.show();
    delay(STROBE_7);
    fadeToBlackBy(leds, NUM_LEDS, 200);
    FastLED.show();
  };
}

#define RATE_8 10
#define STROBE_8 100
#define GAP_8 10
#define NUM_X_8 12
int start_hue_8;
int delta_hue_8 = 20;
int ROW_8 = NUM_LEDS / NUM_X_8;

void corner_to_corner_rainbow()
{
  Serial.println("pattern_8");
  start_hue_8 = -1 * millis() / RATE;
  for (int i = 0; i < ROW_8; i++)
  {
    // Row 1
    leds[i] = CHSV(start_hue_8, 255, 255);
    // Row 2
    leds[ROW_8 + i] = CHSV(start_hue_8, 255, 255);
    // Row 3
    leds[i + (ROW_8 * 2)] = CHSV(start_hue_8, 255, 255);
    // Row 4
    leds[ROW_8 * 4 - 1 - i] = CHSV(start_hue_8, 255, 255);
    // Row 5
    leds[ROW_8 * 5 - 1 - i] = CHSV(start_hue_8, 255, 255);
    // Row 6
    leds[ROW_8 * 5 + i] = CHSV(start_hue_8, 255, 255);
    // Row 8
    leds[i + ROW_8 * 6] = CHSV(start_hue_8, 255, 255);
    // Row 8
    leds[ROW_8 * 8 - 1 - i] = CHSV(start_hue_8, 255, 255);
    // Row 9
    leds[i + ROW_8 * 8] = CHSV(start_hue_8, 255, 255);
    // Row 10
    leds[ROW_8 * 10 - 1 - i] = CHSV(start_hue_8, 255, 255);
    // Row 11
    leds[i + ROW_8 * 10] = CHSV(start_hue_8, 255, 255);
    // Row 12
    leds[NUM_LEDS - 1 - i] = CHSV(start_hue_8, 255, 255);

    start_hue_8 += delta_hue_8;
    FastLED.show();
    delay(STROBE_8);
    fadeToBlackBy(leds, NUM_LEDS, 100);
    FastLED.show();
  };
}

#define RATE_9 10
#define STROBE_9 20
#define GAP_9 10

void all_fade()
{
  Serial.println("pattern_9");
  for (int i = 50; i < 150; i++)
  {
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, i)); // Set all to Off.
    delay(STROBE_9);
    FastLED.show();
  }

  for (int i = 150; i > 50; i--)
  {
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, i)); // Set all to Off.
    delay(STROBE_9);
    FastLED.show();
  }
}

#define RATE_10 10
#define STROBE_10 100
#define GAP_10 10
#define NUM_X_10 12
int start_hue_10;
int delta_hue_10 = 20;
int ROW_10 = NUM_LEDS / 3;

void shooting_stars()
{
  Serial.println("pattern_10");
  start_hue_10 = -1 * millis() / RATE;
  for (int i = 0; i < ROW_10; i++)
  {
    leds[i] = CHSV(start_hue_10, 0, 255);
    leds[i + 60] = CHSV(start_hue_10, 0, 255);
    leds[i + 96] = CHSV(start_hue_10, 0, 255);
    start_hue_10 += delta_hue_10;
    FastLED.show();
    delay(STROBE_10);
    fadeToBlackBy(leds, NUM_LEDS, 200);
    FastLED.show();
  };
}
