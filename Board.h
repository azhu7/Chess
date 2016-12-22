/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

extern const int kNumRows;
extern const int kNumCols;

// Pieces are stored in 8x8 array of pointers to pieces
class Board {
private:
	Piece ***board_;  // 8x8 board of pointers to pieces
	Player turn_;  // Tracks whose turn it is

	// EFFECTS  Generate a dynamically allocated Piece object
	Piece *piece_factory(const Player color, const int col,
		const int row, const char type) const;

	// EFFECTS  Places pawns on board during initialization
	void place_pawns();

	// EFFECTS  Places non-pawn pieces on board during initialization
	void place_pieces();

	// EFFECTS  Updates whose turn it is
	void switch_turns();

	// EFFECTS  Swaps the pointed-to pieces.
	//			Used in Board::move() for moving pieces around.
	void swap(Piece *&p1, Piece *&p2);

	// EFFECTS  Determine if tile coordinates are valid
	bool tile_in_bounds(const int col_in, const int row_in) const;

	// EFFECTS  Determine if piece can be moved to new tile
	//			Calls Piece::valid_placement() and Piece::valid_move() to
	//			make sure piece moves according to Chess rules
	bool valid_move(const int old_col, const int old_row,
		const int new_col, const int new_row) const;

public:
	Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return reference to Piece pointer at specified tile
	Piece *&get_tile(const int col, const int row) const;

	// EFFECTS  Return current player as string
	std::string get_current_player() const;

	// REQUIRES Straight path from old pos to new pos
	// EFFECTS  Return true if there are no pieces from old pos to new pos.
	//			Used by Bishop, Rook, and Queen.
	bool path_is_clear(const int old_col, const int old_row,
		const int new_col, const int new_row) const;

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	bool move(const int old_col, const int old_row,
		const int new_col, const int new_row);

	// EFFECTS  Pretty print the board
	friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

#endif // BOARD_H