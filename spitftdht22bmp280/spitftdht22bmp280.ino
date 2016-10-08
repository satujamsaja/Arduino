/*
 * 1.8 SPI TFT 128x160 test sketch display data from DHT 22 and BMP280
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <SPI.h>
#include "Ucglib.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

/*
 * DHT Out: Digital pin 2
 */
#define DHTPIN 2
#define DHTTYPE DHT22

/* 
 *  Use HW SPI for much faster
 *  Pinouts:
 *  DC: Digital pin 9
 *  CS: Digital pin 10
 *  RESET: Digital pin 8
 */

// init ucglib
Ucglib_ST7735_18x128x160_HWSPI ucg(/*dc=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

// init bmp using I2C
Adafruit_BMP280 bme;

// init DHT 22
DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_ncenR10_hr);
  ucg.clearScreen();

  if (!bme.begin())
  {  
    ucg.setColor(255,255,255);
    ucg.setPrintPos(10,20);
    ucg.print("Failed to initialize!");
    while (1);
  }

  // dht
  dht.begin();

  delay(1000);
  ucg.clearScreen();
  ucg.setPrintPos(10,20);
  ucg.print("Initialize...");
  delay(3000);
}

void loop()
{
  
  // get sensors update
  float humidity = dht.readHumidity();
  float celcius = dht.readTemperature(); // celcius is default output
  float fahrenheit = dht.readTemperature(true); // set true to read in fahrenheit
  
  // skip if error occured
  if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // render ui
  // set color frame box
  ucg.setColor(255,255,255);
  ucg.drawFrame(0, 0, 128, 160);
  ucg.drawFrame(2, 2, 124, 156);

  
  ucg.setColor(255,0,0);
  ucg.drawBox(3,30, 122, 32);
  ucg.setColor(0,255,0);
  ucg.drawBox(3,62, 122, 32);
  ucg.setColor(0,0,255);
  ucg.drawBox(3,94, 122, 32);
  ucg.setColor(0,255,255);
  ucg.drawBox(3,126, 122, 32);
  
  // gradient box
  ucg.setColor(0, 255, 0, 0);
  ucg.setColor(1, 0, 255, 0);
  ucg.setColor(2, 255, 0, 255);
  ucg.setColor(3, 0, 255, 255);
  ucg.drawGradientBox(3, 3, 123, 28);

  // text
  ucg.setColor(255,255,255);
  ucg.setPrintPos(10,20);
  ucg.print("Env Monitoring");
  ucg.setColor(255,255,255);
  ucg.setPrintPos(10,53);
  ucg.print("T:");
  ucg.setColor(0,0,0);
  ucg.setPrintPos(10,85);
  ucg.print("H:");
  ucg.setColor(255,255,255);
  ucg.setPrintPos(10,115);
  ucg.print("P:");
  ucg.setColor(0,0,0);
  ucg.setPrintPos(10,147);
  ucg.print("A:");
  
  // display temperature
  ucg.setColor(255,255,255);
  ucg.setPrintPos(30,53);
  ucg.print(celcius);
  ucg.setPrintPos(64,53);
  ucg.print(" *C");
  
  // display humidity
  ucg.setColor(0,0,0);
  ucg.setPrintPos(30,85);
  ucg.print(humidity);
  ucg.setPrintPos(64,85);
  ucg.print(" %");

  // display pressure
  ucg.setColor(255,255,255);
  ucg.setPrintPos(30,115);
  ucg.print(bme.readPressure() / 100,2);
  ucg.setPrintPos(84,115);
  ucg.print("mb");

  // display approx altitude
  ucg.setColor(0,0,0);
  ucg.setPrintPos(30,147);
  ucg.print(bme.readAltitude(1013.25));
  ucg.setPrintPos(68,147);
  ucg.print("m");
  delay(2000);

}
