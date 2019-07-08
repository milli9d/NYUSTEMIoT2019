#include <Adafruit_STMPE610.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#ifdef ESP8266
#define STMPE_CS 16
#define TFT_CS   0
#define TFT_DC   15
#define SD_CS    2
#endif

#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

#define b 80

int mat[9][2];

int p = 0;          //To track who's turn , 0 is RED , 1 is BLUE
int p1scr = 0;      //to track score
int p2scr = 0;
int touch = 0;      //to track touch
int xb = 0;
int yb = 0;
int offset = 25;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

//To Detect Touch and increment touch counter by 1 , use the counter to actually work with touches using if-else statements
int detectTouch(int x1, int y1, int width, int height);

//break when touch detect , used for traversing screens
void breakTouch(int x1, int y1, int width, int height);

unsigned long testRects(uint16_t color);

void drawColorGrid(int color);

unsigned long welcomeScreen();

void drawstartGrid(int color);

void printShape(int xb0, int yb0, int box);

void redWins(int mat[9][2]);

void blueWins(int mat[9][2]);

void redWon();

void blueWon();

void gameStart();

void draw();
