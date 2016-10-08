/*
 * 1.8 SPI TFT 128x160 test sketch
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <SPI.h>
#include "Ucglib.h"

/* 
 *  Use HW SPI for much faster
 *  Pinouts:
 *  DC: Digital pin 9
 *  CS: Digital pin 10
 *  RESET: Digital pin 8
 */

Ucglib_ST7735_18x128x160_HWSPI ucg(/*dc=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

void setup()
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_ncenR10_hr);
  ucg.clearScreen();
}

void loop()
{
  // set color frame box
  //ucg.setColor(255, 0, 0);
  //ucg.drawBox(0, 0, 128, 160);
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
  delay(1000);  

}
