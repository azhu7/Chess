/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for King piece
*/

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
	explicit King(const Player color = Player::WHITE, const Tile &pos = Tile())
		: Piece{ color, pos }, moved_{ false } {}
	~King() {}

	// Inherited from Piece base class
	const char get_type() const { return 'K'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const;

private:
	bool moved_;  // Can only castle if !moved
};

#endif  // KING_H