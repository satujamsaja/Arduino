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
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22

// init bmp using I2C
Adafruit_BMP280 bme;

// init DHT 22
DHT dht(DHTPIN, DHTTYPE);

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
  
void setup()
{
  if (!bme.begin())
  {  
    lcd.setCursor(0,0);
    lcd.print("Failed to initialize!");
    while (1);
  }

  // dht
  dht.begin();

  // lcd
  lcd.begin(20,4);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initialize...");
  delay(3000);
  lcd.clear();
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

    lcd.setCursor(0,0);
    lcd.print("Local Monitoring");
    lcd.setCursor(0,1);
    lcd.print("* T: ");
    lcd.print(celcius);
    lcd.print("*C/");
    lcd.print(fahrenheit);
    lcd.print("*F");
    lcd.setCursor(0,2);
    lcd.print("* H: ");
    lcd.print(humidity);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("* P: ");
    lcd.print(bme.readPressure() / 100,2);
    lcd.print("mb");
    delay(2000);
}
