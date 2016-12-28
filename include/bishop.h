/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Bishop piece
*/

#ifndef BISHOP_H
#define BISHOP_H

#include "linear_piece.h"

class Bishop : public LinearPiece {
public:
	explicit Bishop(const Player color = Player::WHITE, const Tile &pos = Tile())
		: LinearPiece{ color, pos } {}
	~Bishop() {}

	// Inherited from Piece base class
	char get_type() const override { return 'B'; };

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const override {
		return diagonal_path(get_pos(), new_pos) && get_pos() != new_pos;
	}

	// Inherited from LinearPiece class
	Direction get_direction(const Tile &new_pos) const override {
		// Move upwards (N)
		if (new_pos.row > get_row()) {
			return new_pos.col > get_col() ? Direction::NE : Direction::NW;
		}
		// Move downwards (S)
		return new_pos.col > get_col() ? Direction::SE : Direction::SW;
	}
};

#endif  // BISHOP_H