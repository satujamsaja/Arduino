/*
 * GY BMP 280 test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// using I2C
Adafruit_BMP280 bme;

  
void setup() {
  Serial.begin(9600);
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}
  
void loop() {
    Serial.print("---- GY BMP 280 ----------------\n");
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100); // 100 Pa = 1 millibar
    Serial.println(" mb");
    Serial.print("Approx altitude = ");
    Serial.print(bme.readAltitude(1013.25));
    Serial.println(" m");
    Serial.print("--------------------------------\n\n");
    delay(2000);
}
