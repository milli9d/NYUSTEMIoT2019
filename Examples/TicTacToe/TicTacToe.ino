#include "decl.h"
#include "display.h"
#include "logic.h"

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  ts.begin();
  tft.begin();
  
  welcomeScreen();
  drawstartGrid(ILI9341_WHITE);
  gameStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  touch =0;
}
