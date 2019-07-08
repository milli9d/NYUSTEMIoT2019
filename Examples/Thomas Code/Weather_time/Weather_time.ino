#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


#define WIFI_SSID "NaiDunga"
#define WIFI_PASS "72103A2L"

//open weather map api key 
String apiKey= "070965106c09b477ff883277bc4243e9"; 
int status = WL_IDLE_STATUS; 
WiFiClient client; 

// TimeClient settings
const long utcOffsetInSeconds = -14400;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

WiFiUDP ntpUDP;
String  formattedDate;
String dayStamp;
String timeStamp;

NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);
  timeStamp = timeClient.getFormattedTime();
  Serial.println(timeStamp);
  delay(1000);
}
