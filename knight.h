/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Knight piece
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
	explicit Knight(const Player color = Player::WHITE, const Tile &pos = Tile())
		: Piece{ color, pos } {}
	~Knight() {}

	// Inherited from Piece base class
	const char get_type() const { return 'N'; }

	// EFFECTS  Return true if l-shaped path from old pos to new pos
	//			Used by Knight
	bool l_shape_move(const Tile &old_pos, const Tile &new_pos);

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const;
};

#endif  // KNIGHT_H