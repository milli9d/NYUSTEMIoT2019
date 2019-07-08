#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define STMPE_CS 16
#define TFT_CS   0
#define TFT_DC   15
#define SD_CS    2
  
SoftwareSerial mySerial(4,5);


char msgin;
char msgout;
int verticalPos=0;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);             //Screen
  mySerial.begin(9600);            //Communication
  tft.begin();                    // Start the screen
  tft.fillScreen(ILI9341_BLACK);  //Make screen black
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(mySerial.available())
  {           
    msgin = mySerial.read();
    Serial.print(msgin);
    tft.print(msgin);
    delay(5);
  }
  while(Serial.available())
  {
      msgout = Serial.read();
      mySerial.print(msgout);
      delay(5);
  }
 
}
