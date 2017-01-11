/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Queen piece
*/

#ifndef QUEEN_H
#define QUEEN_H

#include "linear_piece.h"

class Queen : public LinearPiece {
public:
	explicit Queen(const Player color = Player::WHITE, const Tile &pos = Tile())
		: LinearPiece{ color, pos } {}
	~Queen() {}

	// Inherited from Piece base class
	PieceType get_type() const override { return PieceType::Q; };

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const override {
		const Tile cur_pos = get_pos();
		return (diagonal_path(cur_pos, new_pos) || horizontal_path(cur_pos, new_pos) ||
			vertical_path(cur_pos, new_pos)) && cur_pos != new_pos;
	}

	// Inherited from LinearPiece class
	Direction get_direction(const Tile &new_pos) const override {
		const Tile cur_pos = get_pos();
		// Move upwards (N)
		if (new_pos.row > cur_pos.row) {
			if (new_pos.col > cur_pos.col) {
				return Direction::NE;
			}
			return new_pos.col < cur_pos.col ? Direction::NW : Direction::N;
		}
		// Move horizontally
		if (new_pos.row == cur_pos.row) {
			return new_pos.col < cur_pos.col ? Direction::W : Direction::E;
		}
		// Move downwards (S)
		if (new_pos.col > cur_pos.col) {
			return Direction::SE;
		}
		return new_pos.col < cur_pos.col ? Direction::SW : Direction::S;
	}
};

#endif  // QUEEN_H