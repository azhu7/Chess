/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*  Version: 1.7
*
*  TODO:
*	 Promotions!!
*	 Verbose output detailing move outcomes
*	 Save feature? Write moves to log for future replay. Fix for promotions.
*	 How to check for correct test output state? Read in board state and check for equality? (overload == for board AND piece)
*	 Stats feature. type stats to see some stats like #moves, pieces captured
*	 Detect check, checkmate, get out of check, stalemate (may need hash for pieces)
*	 Clean up loops: 1-liners, definition conditions
*/

#include "../include/board.h"
#include "../include/move_maker.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <string>

using namespace std;

// Print Functions
void print_instructions();
void print_intro();
void print_prompt(const MoveMaker &move_maker);
void print_quit(const string &log_name, bool write_log);

// Error Messages
void invalid_log_name_msg(const string &log_name);
void invalid_input_msg();

// Parse Functions
void parse_move(const string &input, Tile &old_pos, Tile &new_pos);
int parse_col_label(const char col_label);

// Logging Functions
void log_move(ofstream &ofs, const Tile &old_pos, const Tile &new_pos, 
	const Player player, const bool valid_move);
void log_board_layout(ofstream &ofs, const MoveMaker &move_maker);

int main(int argc, char *argv[]) {
	Board board;
	MoveMaker move_maker{ &board };
	regex move_format{ "[a-h][1-8] [a-h][1-8]" };  // Example: a2 a3
	ofstream out_file;
	string log_name;
	bool write_log = false;
	if (argc == 2) {
		log_name = argv[1];
		out_file.open(log_name);
		if (!out_file.is_open()) {
			invalid_log_name_msg(log_name);
			return 1;
		}
		write_log = true;
		cout << "Writing game log to " << log_name << '\n';
		out_file << "n\n";  // Skip instructions on replay
	}

	print_intro();

	while (true) {
		move_maker.print_board();
		Tile old_pos, new_pos;
		bool valid_move = false;
		while (!valid_move) {
			print_prompt(move_maker);  // Request input from user
			string input;
			if (getline(cin, input)) {
				if (input == "quit") {
					if (write_log) {
						log_board_layout(out_file, move_maker);
						out_file.close();
					}
					print_quit(log_name, write_log);
					return 0;
				}
				else if (input == "help")
					print_instructions();
				else if (regex_match(input.substr(0, 5), move_format)) {
					parse_move(input, old_pos, new_pos);
					Player current_player = move_maker.get_current_player();
					valid_move = move_maker.make_move(old_pos, new_pos);
					if (write_log)
						log_move(out_file, old_pos, new_pos, current_player, 
							valid_move);
				}
				else
					invalid_input_msg();
			}  // if
		}  // while
		cout << '\n';
	}  // while
	return 0;
}

////////// BEGIN PRINT FUNCTIONS //////////

void print_instructions() {
	cout << " --------------------------------\n";
	cout << "| Rules are standard chess rules.|\n";
	cout << "| Usage:                         |\n";
	cout << "|   Move: [a-h][1-8] [a-h][1-8]  |\n";
	cout << "|   Show Instructions: help      |\n";
	cout << "|   Quit: quit                   |\n";
	cout << " --------------------------------\n";
}

void print_intro() {
	cout << "Hello! Welcome to chess.\n";
	cout << "Would you like to see the instructions? (y/n): ";
	char option = 0;
	if (cin >> option && option == 'y')
		print_instructions();
	// Ignore any extra input
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	cout << "Let's get started!\n\n";
}

void print_prompt(const MoveMaker &move_maker) {
	cout << "Player " << move_maker.get_current_player() << "\'s turn. ";
	cout << "Enter your move: ";
}

inline void print_quit(const string &log_name, bool write_log) {
	cout << "Thanks for playing!\n";
	if (write_log)
		cout << "Your game log has been saved to: " << log_name << '\n';
}

////////// BEGIN ERROR MESSAGES //////////

void invalid_log_name_msg(const string &log_name) {
	cerr << "Invalid log name: " << log_name << ".\n";
	cerr << "Exiting now.\n";
}

void invalid_input_msg() {
	cerr << "Invalid input -- try again. Enter \"help\" for instructions.\n";
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
	auto itr = col_labels.find(col_label);
	assert(itr != col_labels.end());
	return itr->second;
}

////////// BEGIN LOGGING FUNCTIONS //////////

// REQUIRES ofs if open
// MODIFIES ofs
// EFFECTS  Write move to log
void log_move(ofstream &ofs, const Tile &old_pos, const Tile &new_pos,
	const Player player, const bool valid_move) {
	assert(ofs.is_open());
	ofs << old_pos << " " << new_pos << "\t// " << player;
	if (!valid_move)
		ofs << " Invalid move";
	ofs << '\n';
}

// REQUIRES ofs is open
// MODIFIES ofs
// EFFECTS  Write board final layout to log
void log_board_layout(ofstream &ofs, const MoveMaker &move_maker) {
	assert(ofs.is_open());
	ofs << "quit\n\nEnd State:\n";
	move_maker.print_board(ofs);
}