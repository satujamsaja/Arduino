/*
 * LCD 2004 test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin(20,4);
  lcd.backlight();
}


void loop()
{

  // note that rows and cols start at 0
  // write display on rows 0 cols 0
  lcd.setCursor(0,0);
  lcd.print("Satujamsaja line 1");
  // write display on rows 1 cols 0
  lcd.setCursor(0,1);
  lcd.print("Line 2 test");
  // write display on rows 2 cols 0
  lcd.setCursor(0,2);
  lcd.print("Line 3 test");
  // write display on rows 2 cols 0
  lcd.setCursor(0,3);
  lcd.print("Line 4 test");
  delay(2000); 

}


