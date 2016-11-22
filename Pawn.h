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
	Pawn(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Pawn() {}

	char get_type() const;

	// REQUIRES (new_col, new_row) tile contains enemy piece, or en passant
	// EFFECTS  Determine if capture is valid
	bool valid_capture(const unsigned new_col, const unsigned new_row) const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char Pawn::get_type() const {
	return 'P';
}

bool Pawn::valid_capture(const unsigned new_col, const unsigned new_row) const {
	// White pawn
	if (get_player() == WHITE) {
		//
		if (abs(new_row - get_row()) != 1) {
			return false;
		}
	}
	// Black pawn

}

bool Pawn::valid_placement(const unsigned new_col, const unsigned new_row) const {
	const int col_diff = new_col - get_col();  // TODO: Put this among code
	// Pawns can only move vertically, unless capturing another piece
	if (new_row != get_row()) {
		return false;
	}
	// White pawn
	if (get_player() == WHITE) {
		// First move can go 1 or 2 tiles up
		if (get_row() == kWhitePawnStart) {
			return (new_col - get_col() == 1) || (new_col - get_col() == 2);
		}
		// Otherwise, can only go 1 tile up
		return new_col - get_col() == 1;
	}
	// Black pawn
	// First move can go 1 or 2 tiles down
	if (get_row() == kBlackPawnStart) {
		return (get_col() - new_col == 1 || get_col() - new_col == 2);
	}
	// Otherwise, can only go 1 tile down
	return get_col() - new_col == 1;
}

#endif // PAWN_H