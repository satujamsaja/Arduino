/*
 * OLED 128x64 0.96" I2c + DS3231 RTC test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <DS3231.h>
#include <OLED_I2C.h>

// Init the DS3231 and OLED.
DS3231 rtc(SDA, SCL);
OLED oled(SDA, SCL, 8);

// Define fonts.
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

Time t;

void setup()
{
  Serial.begin(9600);
  rtc.begin();
  oled.begin();
  oled.setFont(SmallFont);
  
  //rtc.setDOW(MONDAY); // Day of week (1-7/Monday-Sunday)
  //rtc.setTime(14, 51, 00);  // Time hh,mm,ss (24hr format)
  //rtc.setDate(01, 05, 2017);  // Date format: dd,mm,yyyy
}

void loop()
{
   // Time.
   oled.setFont(BigNumbers);
   oled.print(rtc.getTimeStr(), RIGHT, 0);
   // Dow.
   oled.setFont(SmallFont);
   oled.print(rtc.getDOWStr(), RIGHT, 32);
   // Date.
   oled.setFont(SmallFont);
   oled.print(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'), RIGHT, 48);
   // Update screen.
   oled.update();
   delay(1000);
   oled.clrScr();
}

