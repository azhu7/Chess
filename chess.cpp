/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*
*  TODO:
*	 Consider making move struct for brevity
*	 Verbose output detailing moves
*	 Save feature? Write moves to log for future replay
*	 How to check for correct test output state?
*/

#include "Board.h"
#include <iostream>
#include <unordered_map>
#include <exception>

using namespace std;

class InvalidInputException : public exception {
	const char *what() const throw() {
		return "Invalid input\n";
	}
};

const unordered_map<char, int> col_labels {
	{ 'a', 0 },
	{ 'b', 1 },
	{ 'c', 2 },
	{ 'd', 3 },
	{ 'e', 4 },
	{ 'f', 5 },
	{ 'g', 6 },
	{ 'h', 7 }
};

void print_prompt(const Board &board);
void print_quit();
void parse_move(const string &input, int &old_col, int &old_row,
	int &new_col, int &new_row);
int parse_col_label(const char col_label);

int main(int argc, char *argv[]) {
	Board board;
	while (true) {
		cout << board;
		int old_col, old_row, new_col, new_row, option;
		bool valid_move = false;
		while (!valid_move) {
			print_prompt(board);  // Request input from user
			string input;
			if (getline(cin, input)) {
				if (!input.length()) {
					cerr << "Input error\n";  // Get rid of this pls
					return 1;
				}
				switch (input[0]) {
				case 'q': {
					print_quit();
					return 0;
				}
				default: {  // Check lexicographic character instead of default
					// Parse and execute move
					parse_move(input, old_col, old_row, new_col, new_row);
					valid_move = board.move(old_col, old_row, new_col, new_row);
				}
				}
			}
			else {
				// Should never reach here
				cerr << "Input error\n";
				return 1;
			}
		}
		cout << '\n';
	}
	return 0;
}

void print_prompt(const Board &board) {
	cout << board.get_turn() << "\'s turn. ";
	cout << "Enter your move (\"a1 c3\"): ";
}

void print_quit() {
	cout << "Thanks for playing!\n";
	cout << "Your game log has been saved to: _____\n";
}

// REQUIRES input is of format: A1 B2
void parse_move(const string &input, int &old_col, int &old_row,
	int &new_col, int &new_row) {
	old_row = input[1] - '0';
	new_row = input[4] - '0';
	char old_col_label = input[0], new_col_label = input[3];
	old_col = parse_col_label(old_col_label);
	new_col = parse_col_label(new_col_label);
	// Correct index
	--old_row;
	--new_row;
}

// REQUIRES col_label is a valid label
// EFFECTS  Return respective column number
int parse_col_label(const char col_label) {
	assert(col_labels.find(col_label) != col_labels.end());
	return col_labels.at(col_label);
}
