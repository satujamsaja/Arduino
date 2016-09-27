/*
 * GY BMP 280, DHT 22 and LCD test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define DHTPIN 2
#define DHTTYPE DHT22

// init bmp using I2C
Adafruit_BMP280 bme;

// init DHT 22
DHT dht(DHTPIN, DHTTYPE);

// LCD Nokia
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);
  
void setup()
{
  if (!bme.begin())
  {  
    display.setCursor(0,0);
    display.println("Failed!");
    while (1);
  }

  // dht
  dht.begin();

  // lcd
  display.begin();
  display.setContrast(55);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Initialize...");
}
  
void loop()
{

    float humidity = dht.readHumidity();
    float celcius = dht.readTemperature(); // celcius is default output
    float fahrenheit = dht.readTemperature(true); // set true to read in fahrenheit
  
    // skip if error occured
    if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit))
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("MONITORING");
    display.setCursor(0,10);
    display.print(" T(C):");
    display.print(celcius);
    display.print("*C");
    display.setCursor(0,20);
    display.print(" T(F):");
    display.print(fahrenheit);
    display.println("*F");
    display.setCursor(0,30);
    display.print(" H:");
    display.print(humidity);
    display.print("%");
    display.setCursor(0,40);
    display.print(" P:");
    display.print(bme.readPressure() / 100,2);
    display.print("mb");
    display.display();
    delay(2000);
}
