 #include "Menu.h"

void Menu::CreatMenu()
{
	textcolor(10);
	int y = 5;
	for (int i = 0;i < 20;i++)
	{
		gotoxy(75, y);
		cout << "||";
		y++;
	}
	textcolor(14);
	gotoxy(120, 5); cout << "MENU";
	gotoxy(110, 6); cout << "A S W D    : Move";
	gotoxy(110, 7); cout << "Press P    : Pause";
	gotoxy(110, 8); cout << "Press H    : Hint";
	gotoxy(110, 9); cout << "Press SPACE: Check Slution";
	gotoxy(110, 10); cout << "Press ESC  : EXIT";
}