/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>

static const int kNumRows = 8;
static const int kNumCols = 8;

// Pieces are stored in 8x8 array of pointers to pieces
class Board {
private:
	Piece ***board_;  // 8x8 board of pointers to pieces
	Player turn_;  // Tracks whose turn it is

	// EFFECTS  Generate a dynamically allocated Piece object
	Piece *piece_factory(const Player color, const int col,
		const int row, const char type) const;
	void place_pawns();
	void place_pieces();
	void switch_turns();
	void swap(Piece *&p1, Piece *&p2);

	// EFFECTS  Determine if tile is valid
	bool tile_in_bounds(const int col_in, const int row_in) const;

public:
	Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return reference to Piece pointer at specified tile
	Piece *&get_tile(const int col, const int row) const;

	// EFFECTS  Return current player as string
	std::string get_turn() const;

	// EFFECTS  Determine if piece can be moved to new tile
	bool valid_move(const int old_col, const int old_row,
		const int new_col, const int new_row) const;

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	bool move(const int old_col, const int old_row,
		const int new_col, const int new_row);

	// EFFECTS  Pretty print the board
	friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

#endif // BOARD_H