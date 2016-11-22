/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include "Board.h"

using namespace std;

const unordered_map<char, unsigned> col_labels {
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
void get_move(const Board &board, unsigned &old_col, unsigned &old_row, 
	unsigned &new_col, unsigned &new_row);
unsigned parse_col_label(const char col_label);

int main() {
	Board board;
	while (true) {
		cout << '\n' << board;
		unsigned old_col, old_row, new_col, new_row;
		bool valid_move = false;
		while (!valid_move) {
			get_move(board, old_col, old_row, new_col, new_row);
			valid_move = board.move(old_col, old_row, new_col, new_row);
		}
	}
	return 0;
}

void print_prompt(const Board & board) {
	cout << board.get_turn() << "\'s turn. ";
	cout << "Enter your move (\"a1 c3\"): ";
}

void get_move(const Board &board, unsigned & old_col, unsigned & old_row, 
	unsigned & new_col, unsigned & new_row) {
	char old_col_label, new_col_label;
	print_prompt(board);
	cin >> old_col_label >> old_row >> new_col_label >> new_row;
	old_col = parse_col_label(old_col_label);
	new_col = parse_col_label(new_col_label);
	--old_row;  // Correct index
	--new_row;
}

unsigned parse_col_label(const char col_label) {
	assert(col_labels.find(col_label) != col_labels.end());
	return col_labels.at(col_label);
}
