/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cassert>
#include <algorithm>
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

static const int kNumRows = 8;
static const int kNumCols = 8;

// Pieces are stored in 8x8 array of pointers to pieces
class Board {
private:
	Piece ***board_;  // 8x8 board of pointers to pieces
	Player turn_;  // Tracks whose turn it is

	Piece *piece_factory(const Player color, const unsigned col, 
		const unsigned row, const char type) const;
	void place_pawns();
	void place_pieces();
	void switch_turns();
	void swap(Piece *&p1, Piece *&p2);
public:
	Board();
	~Board();

	// REQUIRES row and col are valid
	// EFFECTS  Return pointer to piece at specified tile
	Piece *&check_tile(const unsigned col, const unsigned row) const;

	// EFFECTS  Return current player as string
	std::string get_turn() const;

	// REQUIRES (old_col, old_row) are coordinates of a piece
	// EFFECTS  Determine if piece can be moved to new tile
	bool valid_move(const unsigned old_col, const unsigned old_row,
		const unsigned new_col, const unsigned new_row) const;

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	bool move(const unsigned old_col, const unsigned old_row,
		const unsigned new_col, const unsigned new_row);

	// EFFECTS  Pretty print the board
	friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

inline Piece *Board::piece_factory(const Player color, const unsigned col, 
	const unsigned row, const char type) const {
	switch (type) {
	case 'P': return new Pawn(color, col, row);
	case 'N': return new Knight(color, col, row);
	case 'B': return new Bishop(color, col, row);
	case 'R': return new Rook(color, col, row);
	case 'Q': return new Queen(color, col, row);
	case 'K': return new King(color, col, row);
	default: {
		std::cerr << "Error: Invalid piece type " << type << '\n';
		exit(1);
	}
	}
}

inline void Board::place_pawns() {
	const unsigned white_pawn_row = 1, black_pawn_row = 6;
	const char pawn = 'P';
	for (unsigned col = 0; col < kNumRows; ++col) {
		board_[white_pawn_row][col] = piece_factory(Player::WHITE, col, white_pawn_row, pawn);
		board_[black_pawn_row][col] = piece_factory(Player::BLACK, col, black_pawn_row, pawn);
	}
}

inline void Board::place_pieces() {
	const char kPieceKey[kNumCols]{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
	const unsigned white_row = 0, black_row = 7;
	for (int col = 0; col < kNumCols; ++col) {
		board_[white_row][col] = piece_factory(Player::WHITE, col, white_row, kPieceKey[col]);
		board_[black_row][col] = piece_factory(Player::BLACK, col, black_row, kPieceKey[col]);
	}
}

inline void Board::switch_turns() {
	turn_ = turn_ == WHITE ? BLACK : WHITE;
}

inline void Board::swap(Piece *&p1, Piece *&p2) {
	Piece *temp = p2;
	p2 = p1;
	p1 = temp;
}

Board::Board() 
	: turn_{ Player::WHITE } {
	board_ = new Piece**[kNumRows];
	for (int i = 0; i < kNumCols; ++i) {
		board_[i] = new Piece*[kNumCols] {nullptr};
	}
	place_pawns();
	place_pieces();
}

Board::~Board() {
	for (int row = 0; row < kNumRows; ++row) {
		// Delete all pieces in column
		for (int col = 0; col < kNumCols; ++col) {
			delete board_[row][col];
			board_[row][col] = nullptr;
		}
		// Delete column
		delete board_[row];
		board_[row] = nullptr;
	}
	// Delete rows
	delete board_;
	board_ = nullptr;
}

inline Piece *&Board::check_tile(const unsigned col, const unsigned row) const {
	// Check in-bounds requirement
	assert(col >= 0 && col < kNumCols);
	assert(row >= 0 && row < kNumRows);
	return board_[row][col];
}

inline std::string Board::get_turn() const
{
	return player_to_string(turn_);
}

bool Board::valid_move(const unsigned old_col, const unsigned old_row,
	const unsigned new_col, const unsigned new_row) const {
	// TODO: ACCOUNT FOR CAPTURES, ESP PAWNS
	Piece *cur_piece = check_tile(old_col, old_row);
	Piece *new_tile = check_tile(new_col, new_row);
	
	if (!cur_piece) {
		return false;  // Player selected empty tile
	}

	// Player move their own piece
	bool correct_team = cur_piece->get_player() == turn_;
	// Okay placement
	bool placement = cur_piece->valid_placement(new_col, new_row);
	// Can't move onto own piece
	bool same_team = new_tile ? new_tile->get_player() == cur_piece->get_player() : false;

	return correct_team && placement && !same_team;
}

bool Board::move(const unsigned old_col, const unsigned old_row,
	const unsigned new_col, const unsigned new_row) {
	if (!valid_move(old_col, old_row, new_col, new_row)) {
		std::cout << ">>> Invalid move. Try again! <<<\n";
		return false;  // Unsuccessful move
	}

	Piece *&cur_piece = check_tile(old_col, old_row);
	Piece *&target_tile = check_tile(new_col, new_row);
	if (target_tile) {
		// Capture enemy piece
		assert(target_tile->get_player() != turn_);  // Make sure enemy piece
		delete target_tile;
		target_tile = nullptr;
	}
	cur_piece->set_coords(new_col, new_row);
	swap(board_[old_row][old_col], board_[new_row][new_col]);  // Move piece
	switch_turns();
	return true;  // Successful move
}

// EFFECTS  Helper function for printing out column labels
void print_col_labels(std::ostream &os) {
	os << "    ";  // Front padding
	for (int col = 0; col < kNumCols; ++col) {
		os << (char)('a' + col) << "  ";
	}
	os << '\n';
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
	// Print column names
	print_col_labels(os);  // Upper key

	for (int row = kNumRows - 1; row >= 0; --row) {
		os << row + 1 << " | ";  // LHS key
		for (int col = 0; col < kNumCols; ++col) {
			Piece *cur_piece = board.check_tile(col, row);
			if (cur_piece) {
				os << cur_piece;
			}
			else {
				os << "--";
			}
			os << ' ';
		}
		os << " | " << row + 1 << '\n';  // RHS key
	}

	print_col_labels(os);  // Lower key
	return os;
}

#endif // BOARD_H