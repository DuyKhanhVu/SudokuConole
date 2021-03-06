#pragma once
#include "Screen.h"
class Table :
	public Screen
{
protected:
	int **Tab;
	int **Sol;
	int **Temp;
	int x[9][9];
	int y[9][9];
public:
	void Init();
	bool CheckIn(int i, int j);
	void CreatLoc();
	void CreatTable();
	bool FindSolve();
	void CreatData(string s);
	void InsertData();
	void ShowHint();
	void ShowSolve();
	bool CheckGamerSol();
	bool InGame();
};

