#pragma once
#include <string>
#include <iostream>
#include <string>
#include "cPlayer.h"
using namespace std;

class cHangman
{
private:
	cPlayer* guesser;
	cPlayer* setter;
public:
	cHangman(cPlayer* player1, cPlayer* player2);
	~cHangman();
	void PrintLine();
	void FillLine(int num_spaces, bool line_start, bool line_end);
	void PrintMessage(string message, bool printTop, bool printBottom);
	void DrawHangman(int guessCount);
	void PrintAvaliableLetters(string letters_used);
	void PrintGuess(string word, string guess);
	bool CorrectGuess(char letter_input, string word);
	bool CheckWin(string word, string guess);
	string GetWord();
	string WordWithoutDuplicates(string word);
	void Run();
};


