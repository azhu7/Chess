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
	char get_type() const { return 'R'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const {
		const Tile cur_pos = get_pos();
		return horizontal_path(cur_pos, new_pos) || vertical_path(cur_pos, new_pos);
	}

	// Inherited from LinearPiece class
	Direction get_direction(const Tile &new_pos) const {
		std::cout << "Unimplemented\n";
		return Direction::E;
	}
};

#endif  // ROOK_H