/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*  Version: 1.3
*
*  TODO:
*    Player name for moves
*	 Verbose output detailing moves
*	 Save feature? Write moves to log for future replay
*	 How to check for correct test output state?
*	 Remove Board object from main altogether? (only keep MoveMaker?)
*/

#include "board.h"
#include "move_maker.h"
#include <iostream>
#include <unordered_map>
#include <exception>
#include <regex>
#include <string>
#include <limits>
#include <ios>

using namespace std;

/*class InvalidInputException : public exception {
public:
	InvalidInputException(const char *message)
		: message{ message } {}
	const char *what() const throw() {
		return message;
	}
private:
	const char *message;
};*/

// Print Functions
void print_instructions();
void print_intro();
void print_prompt(const MoveMaker &move_maker);
void print_quit();

// Parse Functions
void parse_move(const string &input, Tile &old_pos, Tile &new_pos);
int parse_col_label(const char col_label);

int main(int argc, char *argv[]) {
	Board board;
	MoveMaker move_maker{ board };
	regex move{ "[a-h][1-8] [a-h][1-8]" };  // Example: a2 a3
	print_intro();

	while (true) {
		cout << board;
		Tile old_pos, new_pos;
		bool valid_move = false;
		while (!valid_move) {
			print_prompt(move_maker);  // Request input from user
			string input;
			if (getline(cin, input)) {
				if (input == "quit") {
					print_quit();
					return 0;
				}
				else if (input == "help") {
					print_instructions();
				}
				else if (regex_match(input, move)) {
					parse_move(input, old_pos, new_pos);
					valid_move = move_maker.make_move(old_pos, new_pos);
				}
				else {
					cerr << "Invalid input -- try again. Enter \"help\" for instructions.\n";
				}
			}
		}
		cout << '\n';
	}
	return 0;
}

////////// BEGIN PRINT FUNCTIONS //////////

void print_intro() {
	void print_instructions();
	char option;
	cout << "Hello! Welcome to chess.\n";
	cout << "Would you like to see the instructions? (y/n): ";
	if (cin >> option && option == 'y') {
		print_instructions();
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();

	cout << "Let's get started!\n\n";
}

void print_instructions() {
	cout << " --------------------------------\n";
	cout << "| Rules are standard chess rules.|\n";
	cout << "| Usage:                         |\n";
	cout << "|   Move: [a-h][1-8] [a-h][1-8]  |\n";
	cout << "|   Show Instructions: help      |\n";
	cout << "|   Quit: quit                   |\n";
	cout << " --------------------------------\n";
}

void print_prompt(const MoveMaker &move_maker) {
	cout << "Player " << move_maker.get_current_player() << "\'s turn. ";
	cout << "Enter your move: ";
}

void print_quit() {
	cout << "Thanks for playing!\n";
	cout << "Your game log has been saved to: _____\n";
}

////////// BEGIN PARSE FUNCTIONS //////////

// REQUIRES input is of format: [a-h][1-8] [a-h][1-8]
void parse_move(const string &input, Tile &old_pos, Tile &new_pos) {
	// Read in rows and correct to zero-indexed
	old_pos.row = input[1] - '0' - 1;
	new_pos.row = input[4] - '0' - 1;
	old_pos.col = parse_col_label(input[0]);
	new_pos.col = parse_col_label(input[3]);
}

// REQUIRES col_label is [a-h]
// EFFECTS  Return respective column number
//          Throws exception if col_label is a valid label
int parse_col_label(const char col_label) {
	static const unordered_map<char, int> col_labels{
		{ 'a', 0 },
		{ 'b', 1 },
		{ 'c', 2 },
		{ 'd', 3 },
		{ 'e', 4 },
		{ 'f', 5 },
		{ 'g', 6 },
		{ 'h', 7 }
	};
	assert(col_labels.find(col_label) != col_labels.end());
	return col_labels.at(col_label);
}