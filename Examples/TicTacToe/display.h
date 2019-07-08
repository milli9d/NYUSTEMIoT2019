int detectTouch(int x1, int y1, int width, int height)      //Returns 1 when touched at coordinates , then 1 can be used with if conditions to proceed
{
	TS_Point p = ts.getPoint();
	// Scale from ~0->4000 to tft.width using the calibration #'s
	p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
	p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
	if (p.x > 0 && p.y > 0 && p.x <= 240 && p.y <= 320)
	{
		Serial.print("X = "); Serial.print(p.x);
		Serial.print("\tY = "); Serial.print(p.y);
		Serial.print("\tPressure = "); Serial.println(p.z);
		Serial.println(touch);
	}
	if (p.x > x1 && p.x < (x1 + width))
	{
		if (p.y > y1 && p.y < (y1 + height))
		{
			return 1;
		}
	}
	yield();
	delay(20);
	return 0;
}

void breakTouch(int x1, int y1, int width, int height)       //Waits until touched at right place ,then breaks out of loop , used for traversing screens
{
	while (1)
	{
		touch = touch + detectTouch(x1, y1, width, height);
		if (touch == 1)
		{
			break;
		}
	}
}

unsigned long testRects(uint16_t color) {
	unsigned long start;
	int           n, i, i2,
		cx = tft.width() / 2,
		cy = tft.height() / 2;

	tft.fillScreen(ILI9341_BLACK);
	n = min(tft.width(), tft.height());
	start = micros();
	for (i = 2; i < n; i += 6) {
		i2 = i / 2;
		tft.drawRect(cx - i2, cy - i2, i, i, color);
		delay(20);
	}
	return micros() - start;
}

void drawColorGrid(int color) {
	tft.fillRect(0 * b, 1 * b, 3 * b, 3 * b, color);
	tft.drawRect(1 * b, 1 * b, 1 * b, 3 * b, ILI9341_BLACK);
	tft.drawRect(0 * b, 2 * b, 3 * b, 1 * b, ILI9341_BLACK);
}

unsigned long welcomeScreen() {
	unsigned long start = micros();
	tft.fillScreen(ILI9341_BLACK);
	delay(1000);
	yield();
	testRects(ILI9341_BLUE);
	tft.setCursor(35, 145);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(4);
	tft.println("Welcome!");
	delay(1000);
	tft.fillScreen(ILI9341_RED);
	tft.setCursor(0, 70);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(8);
	tft.println("TIC");
	delay(200);
	tft.println("TAC");
	delay(200);
	tft.println("TOE");
	delay(400);
	tft.drawRect(160, 70, 60, 184, ILI9341_WHITE);
	yield();
	delay(1000);
	breakTouch(160, 70, 60, 184);
}

void drawstartGrid(int color) {
	tft.fillScreen(ILI9341_WHITE);
	tft.fillRect(0, 0, 119, 79, ILI9341_RED);
	tft.setCursor(4, 10);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
	tft.println("RED");
	tft.setTextSize(5);
	tft.setCursor(84, 10);
	tft.println(p1scr);
	tft.fillRect(121, 0, 119, 79, ILI9341_BLUE);
	tft.setCursor(124, 10);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
	tft.println("BLUE");
	tft.setTextSize(5);
	tft.setCursor(204, 10);
	tft.println(p2scr);
	drawColorGrid(color);
}

void printShape(int xb0, int yb0, int box) {
	if (p == 1)                       //Red Player is X , mat[][0]
	{
		Serial.println("X");
		tft.drawRect(xb0*b, yb0*b, 1 * b, 1 * b, ILI9341_WHITE);
		tft.fillRect(xb0*b, yb0*b, 1 * b, 1 * b, ILI9341_RED);
		tft.setCursor(((xb0*b) + offset), ((yb0*b) + offset));
		tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(6);
		mat[box][0] = 1;
		tft.print("X");
		p = 0;
	}
	else                          //Blue Player is Y
	{
		Serial.println("Y");
		tft.drawRect(xb0*b, yb0*b, 1 * b, 1 * b, ILI9341_WHITE);
		tft.fillRect(xb0*b, yb0*b, 1 * b, 1 * b, ILI9341_BLUE);
		tft.setCursor(((xb0*b) + offset), ((yb0*b) + offset));
		tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(6);
		mat[box][1] = 1;
		tft.print("O");
		p = 1;
	}
	//delay(800);
}

void draw() {                          //What happens when nobody wins
	tft.fillScreen(ILI9341_RED);
	tft.setCursor(0, 70);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(8);
	tft.println("DRAW");
	delay(1000);
	drawstartGrid(ILI9341_WHITE);
	gameStart();
}

void redWon() {                          //What happens after Red wins
	p1scr++;
	tft.fillScreen(ILI9341_RED);
	tft.setCursor(0, 70);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(8);
	tft.println("RED");
	tft.println("WINS");
	delay(250);
	drawstartGrid(ILI9341_WHITE);
	gameStart();
}

void blueWon() {                          //What happens after Blue wins
	p2scr++;
	tft.fillScreen(ILI9341_BLUE);
	tft.setCursor(0, 70);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(8);
	tft.println("BLUE");
	tft.println("WINS");
	delay(250);
	drawstartGrid(ILI9341_WHITE);
	gameStart();
}
