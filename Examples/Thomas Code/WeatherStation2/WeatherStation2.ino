
#include <Adafruit_STMPE610.h> // touchscreen
#include "ILI9341_SPI.h"
#include <SPI.h>
#include <ESP8266WiFi.h> //wifi
#include <MiniGrafx.h> //graphics
#include <ArduinoJson.h>
#include "NTPClient.h"
#include <WifiUdp.h>
#include "weathericons.h"
#include "fonts.h"
#define STMPE_CS 16
#define TFT_CS   0
#define TFT_DC   15
#define SD_CS    2
#define TFT_LED  5
->
*

#define WHITE1 0xFFFF
#define LIGHTGREEN1 0xC7F9
#define YELLOW1 0xFFE7
#define BLACK1 0x0000
#define BLUE1 0x5C3F
int status= WL_IDLE_STATUS;
float main_temp=0.0;
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>
#define WIFI_SSID "Beau"
#define WIFI_PASS "alfred!*"
int BITS_PER_PIXEL = 2;
uint16_t palette[] = 
{
  BLACK1,
  WHITE1,
  YELLOW1,
  BLUE1,
};

//weather stuff
String OPEN_WEATHER_MAP_LANGUAGE = "en";
const uint8_t MAX_FORECASTS = 10;
String OPEN_WEATHER_MAP_APP_ID = "b9fe0ccf236a412dfc7e2cd6c9e46801";
String OPEN_WEATHER_MAP_LOCATION = "Boston";
const boolean IS_METRIC = true;
#define MAX_FORECASTS 12
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECASTS];

const char* getMeteoconIconFromProgmem(String iconText);
const char* getMeteoconIconFromProgmem(String iconText);

const long utcOffsetInSeconds = -14400; // (3600*4) daylight savings -18000 for UTC-5
WiFiUDP ntpUDP;
NTPClient timeClient (ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
String Date;
String timeStamp;


#include "iconfinder_Weather_408406.h"
ILI9341_SPI tft = ILI9341_SPI (TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);
int updateCounter=0;
WiFiClient client;



void drawProgressBar(int percentage, String text)
{
  gfx.fillBuffer(0);
  gfx.setFont(Lato_Regular_15);
  gfx.setTextAlignment (TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 250, "Thomas Hoffmann");
  gfx.setColor(1);
  gfx.drawString(120, 192, text);
  gfx.setColor(1);
  gfx.drawRect(10,168,240-20,15);
  gfx.setColor(3);
  gfx.fillRect(12,170,216 * percentage/100, 11);
  gfx.drawPalettedBitmapFromPgm(55, 8, weatherIcon);
  gfx.commit();
  
}

void updateweatherData()
  {
    drawProgressBar(50, "Updating conditions...");
    OpenWeatherMapCurrent *currentWeatherClient = new OpenWeatherMapCurrent ();
    currentWeatherClient->setMetric(IS_METRIC);
    currentWeatherClient->setLanguage (OPEN_WEATHER_MAP_LANGUAGE);
    currentWeatherClient->updateCurrent (&currentWeather, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION);
    delete currentWeatherClient;
    currentWeatherClient = nullptr;

    drawProgressBar(70, "Updating forecast...");
    OpenWeatherMapForecast *forecastClient = new OpenWeatherMapForecast ();
    forecastClient->setMetric(IS_METRIC);
    forecastClient->setLanguage (OPEN_WEATHER_MAP_LANGUAGE);
    uint8_t allowedHours[] = {12,0};
    forecastClient->setAllowedHours(allowedHours, sizeof(allowedHours));
    forecastClient->updateForecasts(forecasts, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECASTS);
    delete forecastClient;
    forecastClient = nullptr;

    delay (1000);
  }


void welcomePage()
{
  gfx.fillBuffer(0); //black screen start screen
  gfx.setColor(0);
  gfx.drawString(60,60,"Weather Station");
  gfx.drawPalettedBitmapFromPgm(55, 8, weatherIcon);
  gfx.commit();
  delay(1000);
}


void connectWiFi()
{
  if(WiFi.status() == WL_CONNECTED) return;
    Serial.println("Connecting to WiFi");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    int i = 0;
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if(i>90) {
      i=0;
    }
    i=i+10;
    drawProgressBar(i, "Connecting to WiFi (" + String(WIFI_SSID) +")");
    Serial.print(".");
  }
  drawProgressBar(100, "Connected to WiFi (" + String(WIFI_SSID) +")");
}

  void weatherScreen(){
    gfx.fillBuffer(0);
    gfx.setTextAlignment(TEXT_ALIGN_CENTER);
    gfx.setFont(Lato_Regular_15);
    gfx.setColor(1);
    gfx.drawString(120, 0, Date); //date

   //time 
    gfx.setFont(Lato_Bold_40);
    gfx.setColor(1);
    gfx.drawString(120, 10, timeStamp);
    
   //current weather
    gfx.setFont(Lato_Black_16);
    gfx.setColor(1);
    gfx.drawString(175, 70, String(currentWeather.description));

    gfx.setTextAlignment (TEXT_ALIGN_LEFT);
    gfx.drawPalettedBitmapFromPgm(0, 55, getMeteoconIconFromProgmem(currentWeather.icon));

    gfx.setTextAlignment(TEXT_ALIGN_CENTER);
   
   //temp + weather in 3 hours
    gfx.setFont(Lato_Regular_15);
    gfx.setColor(1);
    gfx.drawString(50, 150, "In 3  hrs");
    gfx.drawString(50, 220, String(int(round(forecasts[0].temp))) + "°" + "C");
    gfx.drawPalettedBitmapFromPgm(30, 170, getMiniMeteoconIconFromProgmem(forecasts[0].icon));

    
    gfx.setFont(Lato_Regular_15);
    gfx.setColor(1);
    gfx.drawString(125, 150, "In 6  hrs");
    gfx.drawString(125, 220, String(int(round(forecasts[1].temp))) + "°" + "C");
    gfx.drawPalettedBitmapFromPgm(100, 170, getMiniMeteoconIconFromProgmem(forecasts[1].icon));

    gfx.setFont(Lato_Regular_15);
    gfx.setColor(1);
    gfx.drawString(200, 150, "In 9  hrs");
    gfx.drawString(200, 220, String(int(round(forecasts[2].temp))) + "°" + "C");
    gfx.drawPalettedBitmapFromPgm(170, 170, getMiniMeteoconIconFromProgmem(forecasts[2].icon));
  
  //Current temp
    gfx.setTextAlignment(TEXT_ALIGN_LEFT);
    gfx.setFont(Lato_Bold_45);
    gfx.setColor(1);
    gfx.drawString(120, 90, String(int(round(currentWeather.temp))) + "°" + "C");

 // weather icon
 gfx.drawPalettedBitmapFromPgm(0, 55, getMeteoconIconFromProgmem(currentWeather.icon));
    
    //city
    gfx.setTextAlignment(TEXT_ALIGN_CENTER);
    gfx.setFont(Lato_Black_30);
    gfx.setColor(1);
    gfx.drawString(120, 275, OPEN_WEATHER_MAP_LOCATION);
    

    
    gfx.commit();

  }
void setup() 
{
   
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  Serial.begin(115200);

  gfx.init();
  welcomePage();
  connectWiFi();
  timeClient.begin();
  updateweatherData();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCounter++;
  if(updateCounter > 60){
    updateweatherData();
    updateCounter=0;
  }
Serial.println(currentWeather.temp);
while(!timeClient.update()){
      timeClient.forceUpdate();
  }
 Date = timeClient.getFormattedDate();
 Serial.println("Date");
 Serial.print(Date);
 timeStamp = timeClient.getFormattedTime();
 Serial.println("TimeStamp");
 Serial.print(timeStamp);
 
 weatherScreen();
delay(59900);

   

}


//typedef struct OpenWeatherMapCurrentData {
//  // "lon": 8.54,
//  float lon;
//  // "lat": 47.37
//  float lat;
//  // "id": 521,
//  uint16_t weatherId;
//  // "main": "Rain",
//  String main;
//  // "description": "shower rain",
//  String description;
//  // "icon": "09d"
//  String icon;
//  String iconMeteoCon;
//  // "temp": 290.56,
//  float temp;
//  // "pressure": 1013,
//  uint16_t pressure;
//  // "humidity": 87,
//  uint8_t humidity;
//  // "temp_min": 289.15,
//  float tempMin;
//  // "temp_max": 292.15
//  float tempMax;
//  // visibility: 10000,
//  uint16_t visibility;
//  // "wind": {"speed": 1.5},
//  float windSpeed;
//  // "wind": {deg: 226.505},
//  float windDeg;
//  // "clouds": {"all": 90},
//  uint8_t clouds;
//  // "dt": 1527015000,
//  uint32_t observationTime;
//  // "country": "CH",
//  String country;
//  // "sunrise": 1526960448,
//  uint32_t sunrise;
//  // "sunset": 1527015901
//  uint32_t sunset;
//  // "name": "Zurich",
//  String cityName;
//} OpenWeatherMapCurrentData;
