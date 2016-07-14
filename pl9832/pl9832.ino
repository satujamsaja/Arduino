/*
 * Traffic Light RGB Test
 * http://satujamsaja.blogspot.co.id
 */


#include <Adafruit_NeoPixel.h>
#define PIN 6 // digital pin number
#define NUM_PIXELS 3 // number of led
#define DELAY 500 // delay between led

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ400);

void setup()
{
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
}

void loop()
{
  // put your main code here, to run repeatedly:
  for(int i=0; i< NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, trafficLightColor(i));
    strip.show();
    delay(DELAY);
    trafficLampOff();
  }
}

// traffic light function, 0 = red, 2 = yellow, 2 = green
uint32_t trafficLightColor(byte colorCode)
{
  switch(colorCode)
  {
    case 0: return strip.Color(255, 0, 0); break;
    case 1: return strip.Color(255, 255, 0); break;
    case 2: return strip.Color(0, 255, 0); break;
  }
}

// turn off all lamp before light it up
void trafficLampOff()
{
  for(int i=0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, 0x000000);
    strip.show();
  }
}
