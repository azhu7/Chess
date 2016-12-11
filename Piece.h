/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for abstract piece
*/

#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <cassert>

const static enum Player {
	WHITE = 1,
	BLACK = 2
};

// Print Player enum as integer value
static std::ostream &operator<<(std::ostream &os, const Player p) {
	os << (p == WHITE ? '1' : '2');
	return os;
}

// Return Player enum as string value
static std::string player_to_string(const Player p) {
	return p == WHITE ? std::string{ "Player 1" } : std::string{ "Player 2" };
}

class Piece {
private:
	Player color_;
	int row_;
	int col_;

public:
	Piece() {}
	Piece(const Player color_in, const int col_in, const int row_in)
		: color_{ color_in }, col_{ col_in }, row_{ row_in } {}
	Piece(const Piece &other);
	Piece &operator=(const Piece &other);

	~Piece() {}

	Player get_player() const {
		return color_;
	}

	int get_row() const {
		return row_;
	}

	int get_col() const {
		return col_;
	}

	void set_coords(const int col_in, const int row_in) {
		col_ = col_in;
		row_ = row_in;
	}

	// EFFECTS  Return piece type as char ('P' = Pawn, 'R' = Rook, etc.)
	virtual char get_type() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Piece *p);

	// EFFECTS  Determine if piece is physically allowed to move to new position.
	//          Does not take into account other pieces at that position.
	virtual bool valid_placement(const int new_col, 
		const int new_row) const = 0;
};

#endif  //BINARY_H
