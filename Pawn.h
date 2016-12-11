#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <cmath>

// Starting rows
const int kWhitePawnStart = 1;
const int kBlackPawnStart = 6;

class Pawn : public Piece {
private:

public:
	Pawn(const Player color_in, const short col_in, const short row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Pawn() {}

	// Inherited from Piece base class
	char get_type() const { return 'P'; };

	// REQUIRES (new_col, new_row) tile contains enemy piece, or en passant
	// EFFECTS  Determine if capture is valid
	bool valid_capture(const int new_col, const int new_row) const;

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // PAWN_H