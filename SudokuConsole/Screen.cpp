#include "Screen.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

BOOL NT_SetConsoleDisplayMode(HANDLE hOutputHandle, DWORD dwNewMode)
{
	typedef BOOL(WINAPI *SCDMProc_t) (HANDLE, DWORD, LPDWORD);
	SCDMProc_t SetConsoleDisplayMode;
	HMODULE hKernel32;
	BOOL bFreeLib = FALSE, ret;
	const char KERNEL32_NAME[] = "kernel32.dll";

	hKernel32 = GetModuleHandleA(KERNEL32_NAME);
	if (hKernel32 == NULL)
	{
		hKernel32 = LoadLibraryA(KERNEL32_NAME);
		if (hKernel32 == NULL)
			return FALSE;

		bFreeLib = true;
	}

	SetConsoleDisplayMode =
		(SCDMProc_t)GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	if (SetConsoleDisplayMode == NULL)
	{
		SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
		ret = FALSE;
	}
	else
	{
		DWORD tmp;
		ret = SetConsoleDisplayMode(hOutputHandle, dwNewMode, &tmp);
	}

	if (bFreeLib)
		FreeLibrary(hKernel32);

	return ret;
}

void Screen::setFullScreen()
{
	NT_SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), 1);
}

void Screen::CleanScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Screen::gotoxy(SHORT x, SHORT y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void Screen::resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Screen::textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

bool Screen::checkKey(int key)
{
	return GetAsyncKeyState(key);
}

void Screen::Begin()
{
	HANDLE kConsoleColor;
	kConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kConsoleColor, 14);
	gotoxy(40, 10); cout << " _________                        ________        ___________                                        " << endl; Sleep(200);
	gotoxy(40, 11); cout << "|              |           |     |        \\      |           |     |     _/      |           |     " << endl;	 Sleep(200);
	gotoxy(40, 12); cout << "|              |           |     |         \\     |           |     |   _/        |           |     " << endl;	 Sleep(200);
	gotoxy(40, 13); cout << "|              |           |     |          |    |           |     | _/          |           |    " << endl;	 Sleep(200);
	gotoxy(40, 14); cout << "|_________     |           |     |          |    |           |     |/            |           |    " << endl;	 Sleep(200);
	gotoxy(40, 15); cout << "          |    |           |     |          |    |           |     |\\_           |           |    " << endl;	 Sleep(200);
	gotoxy(40, 16); cout << "          |    |           |     |          |    |           |     |  \\_         |           |    " << endl;	 Sleep(200);
	gotoxy(40, 17); cout << "          |    |           |     |         /     |           |     |    \\_       |           |    " << endl;	 Sleep(200);
	gotoxy(40, 18); cout << "__________|    |___________|     |________/      |___________|     |      \\_     |___________|    " << endl;	 Sleep(200);
}

string Screen::SlectLevel()
{
	textcolor(9);
	gotoxy(80, 20); cout << "Choose Level";
	textcolor(10);
	gotoxy(84, 21); cout << "Easy";
	textcolor(14);
	gotoxy(83, 22); cout << "Medium";
	textcolor(12);
	gotoxy(84, 23); cout << "Hard";
	textcolor(121);
	gotoxy(70, 24); cout << "Press W S and SPACE to choose LEVEL";
	textcolor(11);
	int y = 21;
	int value = 1;
	bool choose = false;
	gotoxy(82, y); cout << ">";
	gotoxy(89, y); cout << "<";
	do
	{
		if (kbhit())
		{
			gotoxy(82, y); cout << ">";
			gotoxy(89, y); cout << "<";
			char c = getch();
			if ((c == 'S') && (y < 23))
			{
				gotoxy(82, y); cout << " ";
				gotoxy(89, y); cout << " ";
				y = y++;
				value++;
				gotoxy(82, y); cout << ">";
				gotoxy(89, y); cout << "<";
			}
			if ((c == 'W') && (y > 21))
			{
				gotoxy(82, y); cout << " ";
				gotoxy(89, y); cout << " ";
				y--;
				value--;
				gotoxy(82, y); cout << ">";
				gotoxy(89, y); cout << "<";
			}
			if (c == 32) break;
		}
	} while (!choose);
	if (value == 1) return "Easy";
	else if (value == 2) return "Medium";
	else if (value == 3) return "Hard";
}

void Screen::Loading()
{
	string quotes[10];
	gotoxy(82, 25); cout << "Loading..."; Sleep(500);
	quotes[0] = "Ask not what your country can do for you; ask what you can do for your country.";
	quotes[1] = "If you want something done right, do it yourself.";
	quotes[2] = "Knowledge is power.";
	quotes[3] = "To acquire knowledge, one must study; but to acquire wisdom, one must observe.";
	quotes[4] = "Learn form yesterday, Life for to day, Hope for tomorrow.";
	quotes[5] = "A new Language, a new Life.";
	quotes[6] = "I walk slowly, but I never walk backward.";
	quotes[7] = "Old way won't open new door.";
	quotes[8] = "Remember why you started.";
	quotes[9] = "Good Luck.";
	srand(time(NULL));
	int x = rand() % 10;
	gotoxy(87 - quotes[x].length() / 2, 26); cout << quotes[x];
}

void Screen::Playing()
{
	textcolor(11);
	gotoxy(65, 1); cout << " ___         __   ___               ";
	gotoxy(65, 2); cout << "|___  |   | |  \\ |   |  |/""  |   |";
	gotoxy(65, 3); cout << ".___| |___| |__/ |___|  |\\_ |___|  ";
}

void Screen::Win()
{
	textcolor(10);
	gotoxy(62, 27); cout << "_            _  ________  ___         ";
	gotoxy(62, 28); cout << "\\\\          //     ||     ||\\\\  ||";
	gotoxy(62, 29); cout << " \\\\  //\\\\  //      ||     || \\\\ ||";
	gotoxy(62, 30); cout << "  \\\\//  \\\\//    ___||___  ||  \\\\||";
}

bool Screen::LoopGame()
{
	int value = 1;
	textcolor(14);
	gotoxy(72, 32); cout << "DO YOU WANT RESTART?";
	textcolor(10);
	gotoxy(70, 33); cout << "YES";
	textcolor(12);
	gotoxy(90, 33); cout << "NO";

	textcolor(9);
	gotoxy(68, 33); cout << ">>";
	gotoxy(73, 33); cout << "<<";
	for (;;)
	{
		if (kbhit())
		{
			char c = getch();
			if ((c == 'D') && (value == 1))
			{
				gotoxy(68, 33); cout << "  ";
				gotoxy(73, 33); cout << "  ";
				value++;
				gotoxy(88, 33); cout << ">>";
				gotoxy(92, 33); cout << "<<";
			}
			if ((c == 'A') && (value == 2))
			{
				gotoxy(88, 33); cout << "  ";
				gotoxy(92 , 33); cout << "  ";
				value--;
				gotoxy(68, 33); cout << ">>";
				gotoxy(73, 33); cout << "<<";
			}
			if (c == 32) break;
		}
	}
	return (value == 1);
}
