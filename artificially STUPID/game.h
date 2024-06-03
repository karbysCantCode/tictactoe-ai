#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class ticTacToe {
public:
	char ticTacToeHolder[3][3];
	bool win = false;
	char winTeam = '_';
	char turn = 'X';


	void start() {
		memset(ticTacToeHolder, ' ', sizeof(ticTacToeHolder));
		win = false;
		winTeam = '_';
		turn = 'X';
	}

	int draw() {
		for (int y = 0; y < 3; ++y) {
			cout << "       |       |       \n";
			cout << "   " + string(1, ticTacToeHolder[0][y]) + "   |   " + string(1, ticTacToeHolder[1][y]) + "   |   " + string(1, ticTacToeHolder[2][y]) + "   \n";
			cout << "       |       |       \n";
			if (y < 2) {
				cout << "-----------------------\n";
			}
		}
		return 0;
	}

	bool claim(int input) { // true = fail, false succeed
		int x=0;
		int y=0;
		switch (input) {
		case(1):
			break;
		case(2):
			x = 1;
			y = 0;
			break;
		case(3):
			x = 2;
			y = 0;
			break;
		case(4):
			x = 0;
			y = 1;
			break;
		case(5):
			x = 1;
			y = 1;
			break;
		case(6):
			x = 2;
			y = 1;
			break;
		case(7):
			x = 0;
			y = 2;
			break;
		case(8):
			x = 1;
			y = 2;
			break;
		case(9):
			x = 2;
			y = 2;
			break;
		default:
			return true;

		}
		if (ticTacToeHolder[x][y] == ' ') {
			ticTacToeHolder[x][y] = turn;
			return false;
		}
		return true;
	}

	bool checkWin() {
		for (int row = 0; row < 3; ++row) {
			if (ticTacToeHolder[row][0] == turn &&
				ticTacToeHolder[row][1] == turn &&
				ticTacToeHolder[row][2] == turn) {
				return true;
			}
		}

		// Check columns
		for (int col = 0; col < 3; ++col) {
			if (ticTacToeHolder[0][col] == turn &&
				ticTacToeHolder[1][col] == turn &&
				ticTacToeHolder[2][col] == turn) {
				return true;
			}
		}

		// Check diagonals
		if (ticTacToeHolder[0][0] == turn &&
			ticTacToeHolder[1][1] == turn &&
			ticTacToeHolder[2][2] == turn) {
			return true;
		}
		if (ticTacToeHolder[0][2] == turn &&
			ticTacToeHolder[1][1] == turn &&
			ticTacToeHolder[2][0] == turn) {
			return true;
		}

		return false;
	}
};
