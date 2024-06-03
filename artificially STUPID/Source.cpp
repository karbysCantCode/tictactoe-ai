#include <iostream>

#include "game.h"
#include "kai.h"



using namespace std;

int main() {
	bool running = true;
	int input = 0;
	ticTacToe game;
	brain testBrain;
	testBrain.buildBrain();
	testBrain.initInputNeurons(game.ticTacToeHolder);
	while (running) {
		game.start();
		game.draw();
		while (!game.win)
		{

			if (game.turn == 'O') {
				bool invalidInput = true;
				while (invalidInput) {
					int guessed = testBrain.forwardPass(game.ticTacToeHolder);
					cout << endl << guessed << endl;
					invalidInput = game.claim(guessed);
				}
			} else {
				bool invalidInput = true;
				cout << endl << game.turn << "'s turn: ";
				cin >> input;

				invalidInput = game.claim(input);

				while (invalidInput)
				{
					cout << endl << "Invalid input, " << game.turn << "'s turn: ";
					cin >> input;

					invalidInput = game.claim(input);
				}
			}
			game.win = game.checkWin();
			game.winTeam = game.turn;

			if (game.turn == 'X') {
				game.turn = 'O';
			}
			else if (game.turn == 'O') {
				game.turn = 'X';
			}
			game.draw();
			

		}
		
		cout << game.winTeam << " won!" << endl;

	}



	return 0;
};