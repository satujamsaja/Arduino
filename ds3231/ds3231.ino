/*
 * DS3231 RTC test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <DS3231.h>

// Init DS3231.
DS3231 rtc(SDA, SCL);

Time t;

void setup()
{
  Serial.begin(9600);
  rtc.begin();
  
  // Configure RTC module, uncomment below when you want to change the datetime.
  //rtc.setDOW(MONDAY); // Day of week (1-7/Monday-Sunday)
  //rtc.setTime(14, 51, 00);  // Time hh,mm,ss (24hr format)
  //rtc.setDate(01, 05, 2017);  // Date format: dd,mm,yyyy
}

void loop()
{
   Serial.println("----DS3231----");
   Serial.println(rtc.getTimeStr());
   Serial.println(rtc.getDOWStr());
   Serial.println(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'));
   delay(1000);
}

