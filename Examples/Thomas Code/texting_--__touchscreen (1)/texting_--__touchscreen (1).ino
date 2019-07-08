#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
   #define STMPE_CS 16
   #define TFT_CS   0
   #define TFT_DC   15
   #define SD_CS    2
#include <SoftwareSerial.h>
#include <Adafruit_STMPE610.h>
#define BOXSIZE 40
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750




char msgin;
char msgout;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

SoftwareSerial myserialport(2,16);

void setup() {

  tft.begin();
  
  tft.fillScreen(ILI9341_BLACK);                                           
  Serial.begin(9600); //115200,N,8,1  //screen
  myserialport.begin(9600);  
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_MAGENTA); 
  tft.setTextSize(2);
  tft.println("Messages: Daniel");
  tft.drawRect(175,250, BOXSIZE, BOXSIZE, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); 
  tft.setTextSize(1);
  tft.setCursor(179,265);
  tft.println("Clear");
  bool screen = ts.begin();
  TS_Point p = ts.getPoint();// data type for touch location
  p.x = 0;
  p.y = 0;
  delay(1000);//communication
}

void loop() {
  
       TS_Point p = ts.getPoint();
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());// scales value
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.print(p.x);
  Serial.print("\t");
  Serial.println(p.y);
  if (p.x>=185&&p.x<240&&p.y>=260&&p.y<320){
    Serial.println("Cleared");
    tft.fillScreen(ILI9341_BLACK);
    tft.drawRect(175,250, BOXSIZE, BOXSIZE, ILI9341_WHITE);
    tft.setTextColor(ILI9341_WHITE); 
    tft.setTextSize(1);
    tft.setCursor(179,265);
    tft.println("Clear");
    
  } 
  
  delay(2);                                               
while (myserialport.available())
  {
  msgin=myserialport.read();

  Serial.print(msgin);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print(msgin);
  delay(5);
  }
  
while(Serial.available())
  {
  msgout=Serial.read();
  myserialport.print(msgout);

  Serial.print(msgout);
  delay(5);
  
  }
 
}
