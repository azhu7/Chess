/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

extern const int kNumRows;
extern const int kNumCols;

// Simple board: pieces are stored in 8x8 array of pointers to pieces.
// Provides functions for accessing and updating board.
// MoveMaker wrapper required to reinforce rules for making certain moves.
class Board {
public:
	explicit Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return reference to Piece pointer at specified tile
	Piece *&get_tile(const Tile &pos) const {
		// Check in-bounds requirement
		assert(pos.col >= 0 && pos.col < kNumCols);
		assert(pos.row >= 0 && pos.row < kNumRows);
		return board_[pos.row][pos.col];
	}

	// MODIFIES board_
	// EFFECTS  Places piece on board_ at specified tile
	void set_tile(const Tile &pos, Piece *piece) {
		board_[pos.row][pos.col] = piece;
	}

	// EFFECTS  Determine if tile coordinates are valid
	bool tile_in_bounds(const Tile &pos) const {
		return pos.col >= 0 && (pos.col < kNumCols) &&
			(pos.row >= 0) && (pos.row < kNumRows);
	}

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	void move(const Tile &old_pos, const Tile &new_pos) {
		swap(get_tile(old_pos), get_tile(new_pos));
	}

	// EFFECTS  Pretty print the board
	// TODO		This doesn't need to be a friend function...
	friend std::ostream &operator<<(std::ostream &os, const Board &board);

private:
	Piece ***board_;  // 8x8 board of pointers to pieces

	// EFFECTS  Generate a dynamically allocated Piece object
	Piece *piece_factory(const Player color, const Tile &pos,
		const char type) const;

	// MODIFIES board_
	// EFFECTS  Places pawns on board during initialization
	void place_pawns();

	// MODIFIES board_
	// EFFECTS  Places non-pawn pieces on board during initialization
	void place_pieces();

	// MODIFIES p1 and p2
	// EFFECTS  Swaps the pointed-to pieces.
	//			Used in Board::move() for moving pieces around.
	void swap(Piece *&p1, Piece *&p2) {
		Piece *temp = p2;
		p2 = p1;
		p1 = temp;
	}
};

#endif // BOARD_H