#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "windows.h"

using namespace std;

class Screen
{
public:
	void CleanScreen();
	void gotoxy(SHORT x, SHORT y);
	void resizeConsole(int width, int height);
	void textcolor(int x);
	void setFullScreen();
	bool checkKey(int key);

	void Begin();
	string SlectLevel();
	void Loading();
	void Playing();
	void Win();
	bool LoopGame();
};