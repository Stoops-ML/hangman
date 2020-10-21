#include "cPlayer.h"
#include "cHangman.h"
#include <iostream>
#include <string>
using namespace std;

cHangman chooseGuesser(cPlayer* player1, cPlayer* player2)
{
	string guesser;
	bool playerSelected = false;

	do {
		cout << "Who's guessing the word? ";
		getline(cin, guesser);
		if (guesser.compare(player1->getName()) == 0)
		{
			cHangman game(player1, player2);
			return game;
		}
		else if (guesser.compare(player2->getName()) == 0)
		{
			cHangman game(player2, player1);
			return game;
		}
		else
		{
			cout << "Name not recognised. Choose from these names: ";
			cout << player1->getName() << " and " << player2->getName() << endl;
			playerSelected = false;
		}
	} while (!playerSelected);

}

int main() {
	cPlayer* player1 = new cPlayer();
	cPlayer* player2 = new cPlayer();
	char playAgain;

	do {
		
		cHangman game = chooseGuesser(player1, player2);
		game.Run();

		cout << "Play again (y/n)? ";
		cin >> playAgain;
	} while (playAgain != 'n');

	cout << "Game stats after " << player1->getGamesPlayed() << " games:" << endl;
	player1->PrintStats();
	player2->PrintStats();

	delete player1, player2;
	return 0;
}