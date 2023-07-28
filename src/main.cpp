#include <Arduino.h>

#include <FastLED.h>

#define LED_STRIP_PIN 5     // Choose any GPIO pin (D5) for the LED strip data line
#define NUM_LEDS 109         // Number of LEDs in your strip

CRGB leds[NUM_LEDS];        // Create an array to store LED colors

#define SWITCH_PIN 2       // Choose any GPIO pin (D2) for the switch
void rainbowMovingEffect();

void setup() {
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Set the switch pin as an input with internal pull-up resistor
  FastLED.show();                   // Initialize LED strip (all LEDs off)
}

void loop() {
  // Read the state of the switch
  bool switchState = digitalRead(SWITCH_PIN) == HIGH; // Low means the switch is activated
  delay(20);
  if (switchState) {
    rainbowMovingEffect(); // Replace this with your desired color pattern or animation function
  } else {
    FastLED.clear(); // Turn off all LEDs
    FastLED.show();
  }
}

void rainbowMovingEffect() {
  static uint8_t startIndex = 0;
  static uint8_t animationDelay = 50;

  // Update the LED colors
  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = ((i * 256 / NUM_LEDS) + startIndex) % 256;
    leds[i] = CHSV(hue, 255, 255);
  }

  FastLED.show();

  // Increment the startIndex for the next frame of animation
  startIndex++;

  // Reset the startIndex when it reaches the end of the LED strip
  if (startIndex >= 256) {
    startIndex = 0;
  }

  delay(animationDelay);
}





