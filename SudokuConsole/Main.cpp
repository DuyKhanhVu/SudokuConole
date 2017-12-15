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
		Tab.CreatData(level);
		Tab.FindSolve();
		system("cls");
		Tab.CreatTable();
		Tab.InsertData();
		Menu Menu;
		Menu.CreatMenu();
		Scr.Playing();
		for (;;)
		{
			endGame = Tab.InGame();
			if (endGame == false) break;
		}
		//Sleep(2000);
	} while (endGame);
	//system("pause");
}