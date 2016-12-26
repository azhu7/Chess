/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

static constexpr int kNumRows = 8;  // TODO: Want to define in cpp, but board_ needs here
static constexpr int kNumCols = 8;

// Simple board: pieces are stored in 8x8 array of pointers to pieces.
// Provides functions for accessing and updating board.
// MoveMaker wrapper required to reinforce rules for making certain moves.
class Board {
public:
	explicit Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return reference to Piece pointer at specified tile
	Piece *get_tile(const Tile &pos) const {
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
		set_tile(new_pos, get_tile(old_pos));  // Move piece
		set_tile(old_pos, nullptr);  // old_pos is empty now
	}

	// EFFECTS  Pretty print the board
	// TODO		This doesn't need to be a friend function...but should it be?
	friend std::ostream &operator<<(std::ostream &os, const Board &board);

private:
	Piece *board_[kNumRows][kNumCols];  // 8x8 board of pointers to pieces

	// EFFECTS  Generate a dynamically allocated Piece object
	Piece *piece_factory(const Player color, const Tile &pos,
		const char type) const;

	// MODIFIES board_
	// EFFECTS  Places pawns on board during initialization
	void place_pawns();

	// MODIFIES board_
	// EFFECTS  Places non-pawn pieces on board during initialization
	void place_pieces();
};

#endif  // BOARD_H