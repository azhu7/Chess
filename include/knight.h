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
	char get_type() const override { return 'N'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const override {
		return l_shape_move(new_pos);
	}

private:
	// EFFECTS  Return true if l-shaped path from old pos to new pos
	//			Used by Knight
	bool l_shape_move(const Tile &new_pos) const {
		const int row_abs_diff = abs(new_pos.row - get_row());
		const int col_abs_diff = abs(new_pos.col - get_col());
		return (row_abs_diff == 1 && col_abs_diff == 2) || 
			(row_abs_diff == 2 && col_abs_diff == 1);
	}
};

#endif  // KNIGHT_H