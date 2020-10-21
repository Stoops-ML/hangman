#include <string>
#include <conio.h>
#include <iostream>
using namespace std;
#include "cPlayer.h"
#include "cHangman.h"

const int MESSAGE_WIDTH = 50;
const int MAN_SIZE = 7;
const string MAN[MAN_SIZE] = { "|", "|", "O", "|", "/|\\", "|", "/ \\" };

cHangman::cHangman(cPlayer* player1, cPlayer* player2) 
{
	guesser = player1;
	setter = player2;
}

cHangman::~cHangman()
{
}

void cHangman::PrintLine() 
{
	cout << "+";

	for (int i = 0; i < MESSAGE_WIDTH - 2; i++)
	{
		cout << "-";
	}

	cout << "+" << endl;
}

void cHangman::FillLine(int num_spaces, bool line_start = false, bool line_end = false)
{
	if (line_start)
		cout << "|";

	for (int i = 0; i < num_spaces; i++)
		cout << " ";

	if (line_end)
		cout << "|" << endl;
}

void cHangman::PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
	if (printTop)
		PrintLine();

	if (message.length() > MESSAGE_WIDTH - 4)  // recursive function if string is longer than permitted width
	{
		PrintMessage(message.substr(0, message.length() / 2), false, false);
		PrintMessage(message.substr(message.length() / 2 + 1, message.length()), false, true);
		return;
	}

	int num_empty_spaces = (MESSAGE_WIDTH - 2) / 2 - message.length() / 2;
	FillLine(num_empty_spaces, true);

	cout << message;

	int length_correction = 0;  // make sure odd and even message lengths line up
	if ((message.length() + MESSAGE_WIDTH) % 2 != 0)
		length_correction = 1;

	FillLine(num_empty_spaces - length_correction, false, true);

	if (printBottom)
		PrintLine();

}

void cHangman::DrawHangman(int guessCount)
{
	if (guessCount > MAN_SIZE)  // remove when this is fixed
		cout << "ERROR";

	for (int i = 0; i < guessCount; i++)
		PrintMessage(MAN[i], false, false);
}

void cHangman::PrintAvaliableLetters(string letters_used)
{
	string output;

	PrintMessage("AVAILABLE LETTERS", true, false);

	for (char i = 'a'; i <= 'z'; i++)
	{
		if (letters_used.find(i) == string::npos)  // if letter not in used letters
			output += i;
		else
			output += "_";
		output += " ";
	}

	PrintMessage(output, false, true);
}

void cHangman::PrintGuess(string word, string guess)
{
	string output;

	PrintMessage("CURRENT ANSWER", true, false);

	for (int i = 0; i < word.length(); i++)
	{
		if (guess.find(word[i]) != string::npos)
			output += word[i];
		else
			output += "_";
		output += " ";
	}

	PrintMessage(output, false);
}

bool cHangman::CorrectGuess(char letter_input, string word)
{
	if (word.find(letter_input) != string::npos)
		return true; // letter in word
	return false;  // letter not in word
}

bool cHangman::CheckWin(string word, string guess)
{
	if (word.compare(guess) == 0)
		return true; // game won
	//int x = word.compare(guess);
	//cout << x;
	return false; // game not won
}

string cHangman::WordWithoutDuplicates(string word)
{
	string wordWithoutDuplicates;

	for (int i = 0; i < word.length(); i++)
	{
		if (wordWithoutDuplicates.find(word[i]) == string::npos) // add letter if not contained in string guess
			wordWithoutDuplicates += word[i];
	}

	return wordWithoutDuplicates;
}

string cHangman::GetWord()
{
	cout << "Enter word to be guessed: ";
	string word = "";
	char ch = _getch();
	while (ch != '\r') // prints password-like output
	{
		word.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	cout << endl;

	return word;
}

void cHangman::Run()
{
	PrintMessage("HANG MAN"); 
	string word = GetWord();
	string wordWithoutDuplicates = WordWithoutDuplicates(word);

	int tries = 0;
	bool win = false;
	string guess;
	bool letter_guess;
	char letter_input;

	do
	{
		system("cls");  // windows users
		PrintMessage("HANG MAN");
		DrawHangman(tries);
		PrintAvaliableLetters(guess);
		PrintGuess(word, guess);
		if (win)
			break;

		cout << "Enter letter (a-z): ";
		cin >> letter_input;
		if (guess.find(letter_input) == string::npos) // add letter if not contained in string guess
			guess += letter_input;
		else
			continue;

		letter_guess = CorrectGuess(letter_input, word);
		if (!letter_guess)
			tries++;
			
		win = CheckWin(wordWithoutDuplicates, guess);
		
	} while (tries <= MAN_SIZE);

	if (win)
	{
		PrintMessage(guesser->getName() + " WON!");
		guesser->GameWin();
		setter->GameLoss();
	}
	else
	{
		PrintMessage("Better luck next time " + guesser->getName());
		guesser->GameLoss();
		setter->GameWin();
	}
}

