/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for abstract piece
*/

#ifndef PIECE_H
#define PIECE_H

#include <iostream>

const static enum Player {
	WHITE = 1,
	BLACK = 2
};
std::string player_to_string(const Player p) {
	return p == WHITE ? "Player 1" : "Player 2";
}

class Piece {
private:
	Player color_;
	unsigned row_;
	unsigned col_;

public:
	Piece() {}
	Piece(const Player color_in, const unsigned col_in, const unsigned row_in)
		: color_{ color_in }, col_{ col_in }, row_{ row_in } {}
	Piece(const Piece &other);
	Piece &operator=(const Piece &other);

	~Piece() {}

	Player get_player() const {
		return color_;
	}

	unsigned get_row() const {
		return row_;
	}

	unsigned get_col() const {
		return col_;
	}

	void set_coords(const unsigned col_in, const unsigned row_in) {
		col_ = col_in;
		row_ = row_in;
	}

	virtual char get_type() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Piece *p);

	// EFFECTS  Determine if piece is physically allowed to move to new position.
	//          Does not take into account other pieces at that position.
	virtual bool valid_placement(const unsigned new_col, 
		const unsigned new_row) const = 0;
};

std::ostream &operator<<(std::ostream &os, const Piece *p) {
	os << p->get_player() << p->get_type();
	return os;
}

#endif  //BINARY_H
