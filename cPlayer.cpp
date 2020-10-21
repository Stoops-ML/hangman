#include "cPlayer.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

cPlayer::cPlayer() 
{
	cout << "Enter player name: ";
	getline(cin, name);
	wins = 0;
	losses = 0;
	gamesPlayed = 0;
}

void cPlayer::Reset()
{
	wins = 0;
	losses = 0;
	gamesPlayed = 0;
}

void cPlayer::PrintStats()
{
	cout << "Player " << name << ": ";
	cout << "wins " << wins << ", losses " << losses << endl;
}

int cPlayer::getGamesPlayed()
{
	return gamesPlayed;
}

void cPlayer::GameWin()
{
	wins++;
	gamesPlayed++;
}

void cPlayer::GameLoss()
{
	losses++;
	gamesPlayed++;
}

string cPlayer::getName()
{
	return name;
}
