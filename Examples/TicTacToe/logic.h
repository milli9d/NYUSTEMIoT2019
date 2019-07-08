void redWins(int mat[9][2]) {
	if (mat[0][0] == 1 && mat[1][0] == 1 && mat[2][0] == 1)         //Row1
	{
		redWon();
	}
	else if (mat[3][0] == 1 && mat[4][0] == 1 && mat[5][0] == 1)//row2
	{
		redWon();
	}
	else if (mat[6][0] == 1 && mat[7][0] == 1 && mat[8][0] == 1)//row3
	{
		redWon();
	}
	else if (mat[0][0] == 1 && mat[3][0] == 1 && mat[6][0] == 1)//column1
	{
		redWon();
	}
	else if (mat[1][0] == 1 && mat[4][0] == 1 && mat[7][0] == 1) //col2
	{
		redWon();
	}
	else if (mat[2][0] == 1 && mat[5][0] == 1 && mat[8][0] == 1)  //col3
	{
		redWon();
	}
	else if (mat[0][0] == 1 && mat[4][0] == 1 && mat[8][0] == 1)  //diag1
	{
		redWon();
	}
	else if (mat[2][0] == 1 && mat[4][0] == 1 && mat[6][0] == 1)//diag 2
	{
		redWon();
	}
	else {};                                                //Red Doesn't Win
}

void blueWins(int mat[9][2]) {
	if (mat[0][1] == 1 && mat[1][1] == 1 && mat[2][1] == 1)         //Row1
	{
		blueWon();
	}
	else if (mat[3][1] == 1 && mat[4][1] == 1 && mat[5][1] == 1)//row2
	{
		blueWon();
	}
	else if (mat[6][1] == 1 && mat[7][1] == 1 && mat[8][1] == 1)//row3
	{
		blueWon();
	}
	else if (mat[0][1] == 1 && mat[3][1] == 1 && mat[6][1] == 1)//column1
	{
		blueWon();
	}
	else if (mat[1][1] == 1 && mat[4][1] == 1 && mat[7][1] == 1) //col2
	{
		blueWon();
	}
	else if (mat[2][1] == 1 && mat[5][1] == 1 && mat[8][1] == 1)  //col3
	{
		blueWon();
	}
	else if (mat[0][1] == 1 && mat[4][1] == 1 && mat[8][1] == 1)  //diag1
	{
		blueWon();
	}
	else if (mat[2][1] == 1 && mat[4][1] == 1 && mat[6][1] == 1)//diag 2
	{
		blueWon();
	}
	else {};
}

void gameStart()                  //Tic Tac Toe Game Logic
{
	for (int i = 0; i < 9; i++) {
		mat[i][0] = 0;
		mat[i][1] = 0;
	}
	int i = 9;
	while (i > 0)
	{
		int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
		b1 = detectTouch(0 * b, 1 * b, 1 * b, 1 * b);
		b2 = detectTouch(1 * b, 1 * b, 1 * b, 1 * b);
		b3 = detectTouch(2 * b, 1 * b, 1 * b, 1 * b);
		b4 = detectTouch(0 * b, 2 * b, 1 * b, 1 * b);
		b5 = detectTouch(1 * b, 2 * b, 1 * b, 1 * b);
		b6 = detectTouch(2 * b, 2 * b, 1 * b, 1 * b);
		b7 = detectTouch(0 * b, 3 * b, 1 * b, 1 * b);
		b8 = detectTouch(1 * b, 3 * b, 1 * b, 1 * b);
		b9 = detectTouch(2 * b, 3 * b, 1 * b, 1 * b);
		if (b1 == 1)
		{
			if (mat[0][0] == 0 && mat[0][1] == 0) {
				xb = 0;
				yb = 1;
				printShape(xb, yb, 0);
				i--;
			}
		}
		else if (b2 == 1)
		{
			if (mat[1][0] == 0 && mat[1][1] == 0) {
				xb = 1;
				yb = 1;
				printShape(xb, yb, 1);
				i--;
			}
		}
		else if (b3 == 1)
		{
			if (mat[2][0] == 0 && mat[2][1] == 0) {
				xb = 2;
				yb = 1;
				printShape(xb, yb, 2);
				i--;
			}
		}
		else if (b4 == 1)
		{
			if (mat[3][0] == 0 && mat[3][1] == 0) {
				xb = 0;
				yb = 2;
				printShape(xb, yb, 3);
				i--;
			}
		}
		else if (b5 == 1)
		{
			if (mat[4][0] == 0 && mat[4][1] == 0) {
				xb = 1;
				yb = 2;
				printShape(xb, yb, 4);
				i--;
			}
		}
		else if (b6 == 1)
		{
			if (mat[5][0] == 0 && mat[5][1] == 0) {
				xb = 2;
				yb = 2;
				printShape(xb, yb, 5);
				i--;
			}
		}
		else if (b7 == 1)
		{
			if (mat[6][0] == 0 && mat[6][1] == 0) {
				xb = 0;
				yb = 3;
				printShape(xb, yb, 6);
				i--;
			}
		}
		else if (b8 == 1)
		{
			if (mat[7][0] == 0 && mat[7][1] == 0) {
				xb = 1;
				yb = 3;
				printShape(xb, yb, 7);
				i--;
			}
		}
		else if (b9 == 1)
		{
			if (mat[8][0] == 0 && mat[8][1] == 0) {
				xb = 2;
				yb = 3;
				printShape(xb, yb, 8);
				i--;
			}
		}
		else {};
		redWins(mat);
		blueWins(mat);
		yield();
	}

	draw();
}
