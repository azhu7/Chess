/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "tile.h"

extern const int kNumRows;
extern const int kNumCols;

// Pieces are stored in 8x8 array of pointers to pieces
class Board {
private:
	Piece ***board_;  // 8x8 board of pointers to pieces
	Player turn_;  // Tracks whose turn it is

	// EFFECTS  Generate a dynamically allocated Piece object
	Piece *piece_factory(const Player color, const Tile &pos, 
		const char type) const;

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
	bool tile_in_bounds(const Tile &pos) const;

	// EFFECTS  Determine if piece can be moved to new tile
	//			Calls Piece::valid_placement() and Piece::valid_move() to
	//			make sure piece moves according to Chess rules
	bool valid_move(const Tile &old_pos, const Tile &new_pos) const;

public:
	Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return reference to Piece pointer at specified tile
	Piece *&get_tile(const Tile &pos) const;

	void set_tile(const Tile &pos, Piece *piece);

	// EFFECTS  Return current player
	Player get_current_player() const;

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	bool move(const Tile &old_pos, const Tile &new_pos);

	// EFFECTS  Pretty print the board
	friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

#endif // BOARD_H