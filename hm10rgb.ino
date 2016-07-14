/*
 * Controlling the RGB Led using HM-10 BLE
 * http://satujamsaja.blogspot.co.id
 */

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN 6 // digital pin connected to RGB
#define NUM_PIXELS 3 // number of led used
#define DELAY 500 // set delay for led to turn on

// use SoftwareSerial
SoftwareSerial mySerial(7, 8);  // RX,TX
/*
 * HM-10 RXD pin -> Arduino Pin 8 (TX)
 * HM-10 TXD pin -> Arduini Pin 7 (RX)
 */

// use Adafruit_Neopixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ400);

// initial led state
int lastPixel = 0;

void setup()
{
  // put your setup code here, to run once:
  // turn off led on load
  strip.begin();   
  strip.show();
  
  // begin serial communication 
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  String c;
  int pixel;
  String state;
  String delimiter;
  if (mySerial.available())
  {
    c = mySerial.readString();
    pixel = c.substring(0,1).toInt();
    delimiter = c.substring(0,1);
    state = c.substring(2);
    if(delimiter == "c")
    {
      colorLed(lastPixel, state);
    }
    else
    {
      turnLed(pixel, state);
    }
  }
}

// set pixel color
void colorLed(int pixel,String state)
{ 
  int r  = getStringPartByNr(state, ',', 0).toInt();
  int g  = getStringPartByNr(state, ',', 1).toInt();
  int b  = getStringPartByNr(state, ',', 2).toInt();
  strip.setPixelColor(pixel, r, g, b);
  strip.show();
  lastPixel = pixel;
}

// turn on or off led depend on state
void turnLed(int pixel, String state) {
  if(state == "true")
  {
    strip.setPixelColor(pixel, 0xffffff);
    strip.show();
  }
  else
  {
    strip.setPixelColor(pixel, 0x000000);
    strip.show();
  }
  lastPixel = pixel;
}

// see : https://github.com/BenTommyE/Arduino_getStringPartByNr/blob/master/getStringPartByNr.ino
// small modification with data.length();

String getStringPartByNr(String data, char separator, int index)
{
    // spliting a string and return the part nr index
    // split by separator
    
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text
    
    for(int i = 0; i<data.length(); i++)
    {    //Walk through the text one letter at a time
      
      if(data[i]==separator)
      {
        //Count the number of times separator character appears in the text
        stringData++;
        
      }
      else if(stringData==index)
      {
        //get the text when separator is the rignt one
        dataPart.concat(data[i]);
        
      }
      else if(stringData>index)
      {
        //return text and stop if the next separator appears - to save CPU-time
        return dataPart;
        break;      
      }

    }
    //return text if this is the last part
    return dataPart;
}
