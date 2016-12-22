#include "Pawn.h"

bool Pawn::valid_capture(const int new_col, const int new_row) const {
	std::cout << "TODO: account for en passant\n";
	const int row_diff = new_row - get_row();
	const int col_abs_diff = abs(new_col - get_col());

	// Valid if move left/right 1 column and move up/down 1 row
	// White pawn must capture up one col. Black pawn capture down one col
	return col_abs_diff == 1 && (get_player() == Player::WHITE ? row_diff == 1 : row_diff == -1);
}

bool Pawn::valid_placement(const int new_col, const int new_row) const {
	/*if (!move_in_bounds(new_col, new_row)) {
		return false;
	}*/
	const int row_diff = new_row - get_row();
	const int col_diff = new_col - get_col();

	// Pawns cannot move left/right except to capture (check w/ Pawn::valid_capture())
	if (col_diff) {
		return false;
	}

	// Case 1: white pawn
	if (get_player() == Player::WHITE) {
		// First move can go 1 or 2 tiles up
		if (get_row() == kWhitePawnStart) {
			return (row_diff == 1) || (row_diff == 2);
		}
		// Otherwise, can only go 1 tile up
		return row_diff == 1;
	}
	// Case 2: black pawn
	// First move can go 1 or 2 tiles down
	if (get_row() == kBlackPawnStart) {
		return (row_diff == -1 || row_diff == -2);
	}
	// Otherwise, can only go 1 tile down
	return row_diff == -1;
}