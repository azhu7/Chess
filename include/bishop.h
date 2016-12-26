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
	char get_type() const { return 'B'; };

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const {
		return diagonal_path(get_pos(), new_pos);
	}

	// Inherited from LinearPiece class
	Direction get_direction(const Tile &new_pos) const {
		std::cout << "Unimplemented!!\n";
		return Direction::E;
	}
};

#endif  // BISHOP_H