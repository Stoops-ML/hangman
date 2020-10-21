#pragma once
#include <string>
#include <iostream>
using namespace std;

class cPlayer
{
private:
	string name;
	int wins, losses, gamesPlayed;
public:
	cPlayer();
	void Reset();
	void GameWin();
	void GameLoss();
	void PrintStats();
	string getName();
	int getGamesPlayed();
};


