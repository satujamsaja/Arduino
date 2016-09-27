/*
 * GY BMP 280, DHT 22 and Nokia 5110 LCD test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

void setup()
{
  display.begin();
  display.setContrast(55);
}


void loop()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Satujamsaja");
  display.setCursor(0,15);
  display.println("Line 1");
  display.setCursor(0,25);
  display.println("Line 2");
  display.setCursor(0,35);
  display.println("Line 3");
  display.display();
  delay(2000);     
}

