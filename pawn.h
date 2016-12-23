#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include <cmath>

// Starting rows
const int kWhitePawnStart = 1;
const int kBlackPawnStart = 6;

class Pawn : public Piece {
private:

public:
	Pawn(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~Pawn() {}

	// Inherited from Piece base class
	char get_type() const { return 'P'; };

	// REQUIRES (new_col, new_row) tile contains enemy piece, or en passant
	// EFFECTS  Determine if capture is valid
	bool valid_capture(const Tile &pos) const;

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // PAWN_H