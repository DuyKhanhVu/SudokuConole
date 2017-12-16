#include "Table.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

void Table::Init()
{
	Tab = new int*[9];
	Sol = new int*[9];
	Temp = new int*[9];
	for (int i = 0;i < 9;i++)
	{
		Tab[i] = new int[9];
		Sol[i] = new int[9];
		Temp[i] = new int[9];
	}
	for (int i=0; i<9;i++)
		for (int j = 0;j < 9;j++)
		{
			Sol[i][j] = 0;
			Tab[i][j] = 0;
			Temp[i][j] = 0;
		}
}

bool Table::CheckIn(int i, int j)
{
	if (i < 9 && i >= 0 && j < 9 && j >= 0) return true;
	else return false;
}

void Table::CreatLoc()
{
	int tx = 22;
	int ty = 6;
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			x[i][j] = tx + j * 4;
			y[i][j] = ty + i * 2;
		}
	}
}

int GetLoc(int i, int j)
{
	if (i < 3)
	{
		if (j < 3) return 0;
		else if (j < 6) return 1;
		else return 2;
	}
	else if (i < 6)
	{
		if (j < 3) return 3;
		else if (j < 6) return 4;
		else return 5;
	}
	else if (i < 9)
	{
		if (j < 3) return 6;
		else if (j < 6) return 7;
		else return 8;
	}
	return -1;
}

bool CheckSol(int *Sol[], int &row, int &col)
{
	for (row = 0;row < 9;row++)
		for (col = 0;col < 9;col++)
			if (Sol[row][col] == 0) return false;
	return true;
}

bool Safe(int *Sol[], int row, int col, int num)
{
	//Check Colum
	for (int i = 0;i < 9; i++)
		if (Sol[i][col] == num) return false;
	//Check Row
	for (int j = 0;j < 9; j++)
		if (Sol[row][j] == num) return false;
	//Check Box
	int BoxStartRow = row - row % 3;
	int BoxStartCol = col - col % 3;
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 3;j++)
			if (Sol[i + BoxStartRow][j + BoxStartCol] == num) return false;
	return true;
}

bool Table::FindSolve()
{
	int row, col;
	if (CheckSol(Sol, row, col)) return true;
	for (int num = 1;num <= 9;num++)
	{
		if (Safe(Sol, row, col, num))
		{
			Sol[row][col] = num;
			if (FindSolve()) return true;
			Sol[row][col] = 0;
		}
	}
	return false;
}

void Table::CreatData(string s)
{
	Init();
	int i, j, x, level;
	if (s == "Easy") level = 18;
	else if (s == "Medium") level = 15;
	else if (s == "Hard") level = 12;
	for (int t = 0;t < level;t++)
	{
		bool found = false;
		while (!found)
		{
			srand(time(NULL));
			i = rand() % 9;
			j = rand() % 9;
			x = rand() % 9;
			if (Safe(Sol, i, j, x + 1))
			{
				Tab[i][j] = x + 1;
				Sol[i][j] = x + 1;
				Temp[i][j] = x + 1;
				found = true;
			}
		}
	}
}

void Table::CreatTable()
{
	int x = 24;
	int y = 6;
	textcolor(6);
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			gotoxy(x, y);
			cout << "|";
			x += 4;
		}
		y += 2;
		x = 24;
	}
	
	int t = 7;
	for (int i = 0;i < 8;i++)
	{
		gotoxy(20, t);
		for (int i = 0;i < 9;i++)
			cout << "+---";
		cout << "+";
		t += 2;
	}

	textcolor(9);
	t = 5;
	for (int i = 0;i < 4;i++)
	{
		gotoxy(20, t);
		for (int i = 0;i < 9;i++)
			cout << "+---";
		cout << "+";
		t += 6;
	}

	x = 20;
	y = 7;
	for (int i = 0;i < 9;i++)
	{

		for (int j = 0;j < 4;j++)
		{
			gotoxy(x, y);
			cout << "+";
			x += 12;
		}
		y += 2;
		x = 20;
	}

	x = 20;
	y = 6;
	for (int i = 0;i < 9;i++)
	{

		for (int j = 0;j < 4;j++)
		{
			gotoxy(x, y);
			cout << "|";
			x += 12;
		}
		y += 2;
		x = 20;
	}

}

void Table::InsertData()
{
	//Fill();
	textcolor(12);
	int x = 20;
	int y = 6;
	//gotoxy(22, 6); cout << this->Tab[0][0];
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)

		{
			gotoxy(x + j * 4 + 2, y);
			if (this->Tab[i][j] != 0)
				cout << this->Tab[i][j];
		}
		y = y + 2;
	}
}

void Table::ShowHint()
{
	textcolor(10);
	for (int i = 0;i < 9;i++)
		for (int j = 0;j < 9;j++)
			if ((Tab[i][j] == 0) && (Temp[i][j] == 0))
			{
				gotoxy(x[i][j], y[i][j]);
				cout << Sol[i][j];
				Temp[i][j] = Sol[i][j];
				return;
			}
}

void Table::ShowSolve()
{
	textcolor(10);
	int x = 20;
	int y = 6;
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)

		{
			gotoxy(x + j * 4 + 2, y);
			if (this->Tab[i][j] == 0)
				cout << this->Sol[i][j];
		}
		y = y + 2;
	}
}

bool Check(int *Temp[], int row, int col, int num)
{

	for (int i = 0;i < 9; i++)
		//if (Temp[i][col] == num) return false;
		if ((i != row) && (Temp[i][col] == num)) return false;
	for (int j = 0;j < 9; j++)
		//if (Temp[row][j] == num) return false;
		if ((j != col) && (Temp[row][j] == num)) return false;

	int BoxStartRow = row - row % 3;
	int BoxStartCol = col - col % 3;
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 3;j++)
			//if (Temp[i + BoxStartRow][j + BoxStartCol] == num) return false;
			if ((i+ BoxStartRow != row) && (j +BoxStartCol != col ) && (Temp[i + BoxStartRow][j + BoxStartCol] == num)) return false;
	return true;
}

bool Table::CheckGamerSol()
{
	bool error = true;
	textcolor(14);
	for (int i=0;i<9;i++)
		for (int j = 0;j < 9;j++)
		{
			if (Temp[i][j] == 0)
			{
				gotoxy(x[i][j], y[i][j]);
				cout << "-";
				error = false;
			}
			else if ((Tab[i][j] == 0) && Check(Temp, i, j, Temp[i][j]) == false)
			{
				gotoxy(x[i][j], y[i][j]); cout << Temp[i][j];
				error = false;
			}
		}
	return error;
}


bool Table::InGame()
{
	CreatLoc();
	textcolor(7);
	int i = 0;
	int j = 0;
	gotoxy(x[i][j], y[i][j]);
	do
	{
		if (kbhit())
		{
			char c = getch();
			switch (c)
			{
			case 'W': //UP
				if (CheckIn(i - 1, j))
				{
					i--;
					gotoxy(x[i][j], y[i][j]);
				}
				break;
			case 'S': //DOWN
				if (CheckIn(i + 1, j))
				{
					i++;
					gotoxy(x[i][j], y[i][j]);
				}
				break;
			case 'D': //LEFT
				
				if (CheckIn(i, j + 1))
				{
					j++;
					gotoxy(x[i][j], y[i][j]);
				}break;
			case 'A': //RIGHT
				if (CheckIn(i, j - 1))
				{
					j--;
					gotoxy(x[i][j], y[i][j]);
				}
				break;
			case '1':
				if (Tab[i][j] == 0)
				{
					cout << 1;
					Temp[i][j] = 1;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '2':
				if (Tab[i][j] == 0)
				{
					cout << 2;
					Temp[i][j] = 2;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '3':
				if (Tab[i][j] == 0) 
				{
					cout << 3;
					Temp[i][j] = 3;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '4':
				if (Tab[i][j] == 0) 
				{
					cout << 4;
					Temp[i][j] = 4;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '5':
				if (Tab[i][j] == 0) 
				{
					cout << 5;
					Temp[i][j] = 5;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '6':
				if (Tab[i][j] == 0) 
				{
					cout << 6;
					Temp[i][j] = 6;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '7':
				if (Tab[i][j] == 0) 
				{
					cout << 7;
					Temp[i][j] = 7;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '8':
				if (Tab[i][j] == 0) 
				{
					cout << 8;
					Temp[i][j] = 8;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case '9':
				if (Tab[i][j] == 0) 
				{
					cout << 9;
					Temp[i][j] = 9;
				}
				gotoxy(x[i][j], y[i][j]);
				break;
			case 'H':
				ShowHint();
				textcolor(7);
				gotoxy(x[i][j], y[i][j]);
				break;
			case 'C':
				CheckGamerSol();
				textcolor(7);
				gotoxy(x[i][j], y[i][j]);
				break;
			case 32:
				ShowSolve();
				textcolor(7);
				gotoxy(x[i][j], y[i][j]);
				break;
			case 27:
				return false;
			}
		}
	} while (true);
}
