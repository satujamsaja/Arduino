/*
 * DHT 22 test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 * Install Adafruit DHT Sensor librari from Sketch > Include Library > Manage Libraries
 * Or download from : https://github.com/adafruit/DHT-sensor-library
 * 
 */

// include sensor library
#include "DHT.h"

// digital pin connected to sensor output
#define DHTPIN 2

// DHT Type, valid options : DHT11, DHT21, DHT22
#define DHTTYPE DHT22

// I use DHT 22 with breakout board, so no need to add additional resistor or capacitor, see my blog how to connect it

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.print("");
  dht.begin();
}

void loop()
{
  delay(2000);
  
  float humidity = dht.readHumidity();
  float celcius = dht.readTemperature(); // celcius is default output
  float fahrenheit = dht.readTemperature(true); // set true to read in fahrenheit

  // skip if error occured
  if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("---- DHT 22 --------------------\n");
  Serial.print(" * Humidity: ");
  Serial.print(humidity);
  Serial.print("%\n");
  Serial.print(" * Temperature: ");
  Serial.print(celcius);
  Serial.print("*C/");
  Serial.print(fahrenheit);
  Serial.print("*F\n");
  Serial.print("--------------------------------\n\n");
}

