/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*  Version: 1.2
*
*  TODO:
*    Fix instruction input (next getline gets messed up)
*	 Consider making move struct for brevity
*    Player name for moves
*	 Verbose output detailing moves
*	 Save feature? Write moves to log for future replay
*	 How to check for correct test output state?
*/

#include "Board.h"
#include <iostream>
#include <unordered_map>
#include <exception>
#include <string>

using namespace std;

// If need to throw from board.cpp and
// others, consider moving to separate file?
class InvalidInputException : public exception {
public:
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

void print_instructions();
void print_intro();
void print_prompt(const Board &board);
void print_quit();
void parse_move(const string &input, Tile &old_pos, Tile &new_pos);
int parse_col_label(const char col_label);

int main(int argc, char *argv[]) {
	Board board;
	print_intro();

	while (true) {
		cout << board;
		Tile old_pos, new_pos;
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
				default: {  // TODO: Check lexicographic character instead of default for options
					// Parse and execute move
					try {
						parse_move(input, old_pos, new_pos);
						valid_move = board.move(old_pos, new_pos);
					}
					catch (InvalidInputException e) {
						cerr << e.what();
					}
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

void print_instructions() {
	cout << "Not implemented yet\n";
}

void print_intro() {
	char option = 'n';  // TEMP PLACEHOLDER
	cout << "Hello! Welcome to chess.\n";
	cout << "Would you like to see the instructions? (y/n): ";
	if (option == 'y') {
		print_instructions();
	}
	cout << "Let's get started!\n\n";
}

void print_prompt(const Board &board) {
	cout << "Player " << board.get_current_player() << "\'s turn. ";
	cout << "Enter your move (\"a1 c3\"): ";
}

void print_quit() {
	cout << "Thanks for playing!\n";
	cout << "Your game log has been saved to: _____\n";
}

// REQUIRES input is of format: A1 B2
void parse_move(const string &input, Tile &old_pos, Tile &new_pos) {
	// Read in rows and correct to zero-indexed
	old_pos.row = input[1] - '0' - 1;
	new_pos.row = input[4] - '0' - 1;
	char old_col_label = input[0], new_col_label = input[3];
	try {
		old_pos.col = parse_col_label(old_col_label);
		new_pos.col = parse_col_label(new_col_label);
	}
	catch (InvalidInputException e) {
		throw e;
	}
}

// EFFECTS  Return respective column number
//          Throws exception if col_label is a valid label
int parse_col_label(const char col_label) {
	if (col_labels.find(col_label) == col_labels.end()) {
		throw InvalidInputException();
	}
	return col_labels.at(col_label);
}
