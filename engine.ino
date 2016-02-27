
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D7
#define PIXEL_COUNT 2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
static uint32_t Wheel(byte WheelPos, byte bright) {
    if(WheelPos < 85) {
        return strip.Color(WheelPos * 3 * bright / 256, (255 - WheelPos * 3 ) * bright / 256, 0);
    }
    else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color((255 - WheelPos * 3) * bright / 256, 0, (WheelPos * 3) * bright / 256);
    }
    else {
        WheelPos -= 170;
        return strip.Color(0, (WheelPos * 3) * bright / 256, (255 - WheelPos * 3) * bright / 256);
    }
}

static uint32_t Mix(uint32_t c, byte bright) {
    return strip.Color(
        ((c >> 8) & 0xff) * bright / 256,
        (c >> 16) * bright / 256,
        (c & 0xff) * bright / 256
    );
}

static int x;
static int color;
static int speed;

// this function automagically gets called upon a matching POST request
int setColor(int c) {
    color = c;
    return 1;
}

// this function automagically gets called upon a matching POST request
int setSpeed(int s) {
    speed = s;
    return 1;
}

void setup() {
    pinMode(A0, INPUT);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Particle.function("color", setColor);
    Particle.function("speed", setSpeed);
    // Start out slow rainbow
    color = 0;
    speed = 1;
}


void loop() {
    x = (x + speed) % 256;
    if (color) {
        strip.setPixelColor(0, Mix(color, x));
        strip.setPixelColor(1, Mix(color, (x + 128) % 256));
    }
    else {
        strip.setPixelColor(0, Wheel(x, 50));
        strip.setPixelColor(1, Wheel((x + 128) % 256, 50));
    }
    strip.show();
    delay(16);
}
