/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Rook piece
*/

#ifndef ROOK_H
#define ROOK_H

#include "linear_piece.h"

class Rook : public LinearPiece {
public:
	explicit Rook(const Player color = Player::WHITE, const Tile &pos = Tile())
		: LinearPiece{ color, pos } {}
	~Rook() {}

	// Inherited from Piece base class
	char get_type() const override { return 'R'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const override {
		const Tile cur_pos = get_pos();
		return (horizontal_path(cur_pos, new_pos) || vertical_path(cur_pos, new_pos)) &&
			cur_pos != new_pos;
	}

	// Inherited from LinearPiece class
	Direction get_direction(const Tile &new_pos) const override {
		// Move horizontally
		if (new_pos.row == get_row()) {
			return new_pos.col > get_col() ? Direction::E : Direction::W;
		}
		// Move vertically
		return new_pos.row > get_row() ? Direction::N : Direction::S;
	}
};

#endif  // ROOK_H