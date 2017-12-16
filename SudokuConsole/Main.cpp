#include "Screen.h"
#include "Menu.h"
#include "Table.h"

int main()
{
	Screen Scr;
	bool endGame = true;
	do
	{
		Scr.setFullScreen();
		Scr.Begin();
		
		Sleep(500);
		Table Tab;
		string level = Scr.SlectLevel();
		Scr.Loading();
		while (true)
		{
			Tab.CreatData(level);
			if (Tab.FindSolve()) break;
		}
		system("cls");
		Tab.CreatTable();
		Tab.InsertData();
		Menu Menu;
		Menu.CreatMenu();
		Scr.Playing();
		endGame = Tab.InGame();
		system("cls");
	} while (endGame);
}