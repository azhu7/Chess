#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include <cmath>

// Starting rows
const int kWhitePawnStart = 1;
const int kBlackPawnStart = 6;

class Pawn : public Piece {
public:
	explicit Pawn(const Player color = Player::WHITE, const Tile &pos = Tile())
		: Piece{ color, pos } {}
	~Pawn() {}

	// Inherited from Piece base class
	const char get_type() const { return 'P'; };

	// REQUIRES (new_col, new_row) tile contains enemy piece, or en passant
	// EFFECTS  Determine if capture is valid
	bool valid_capture(const Tile &new_pos) const;

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const;

private:

};

#endif // PAWN_H