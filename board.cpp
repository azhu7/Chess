#include "board.h"
#include "player.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <iostream>
#include <cassert>

const int kNumRows = 8;
const int kNumCols = 8;

////////// BEGIN PUBLIC FUNCTIONS //////////

Board::Board() {
	// Create 8x8 array of nullptrs
	board_ = new Piece**[kNumRows];
	for (int i = 0; i < kNumCols; ++i) {
		board_[i] = new Piece*[kNumCols] {nullptr};
	}
	// Place all pieces onto board
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

	// Print rows from bottom up
	for (int row = kNumRows - 1; row >= 0; --row) {
		Tile cur_tile{ row, 0 };
		os << row + 1 << " | ";  // LHS key
		for (int col = 0; col < kNumCols; ++col) {
			cur_tile.col = col;
			Piece *cur_piece = board.get_tile(cur_tile);
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

////////// BEGIN PRIVATE FUNCTIONS //////////

inline Piece *Board::piece_factory(const Player color, const Tile &pos,
	const char type) const {
	switch (type) {
	case 'P': return new Pawn(color, pos);
	case 'N': return new Knight(color, pos);
	case 'B': return new Bishop(color, pos);
	case 'R': return new Rook(color, pos);
	case 'Q': return new Queen(color, pos);
	case 'K': return new King(color, pos);
	default: {
		std::cerr << "Error: Invalid piece type " << type << '\n';
		exit(1);
	}
	}
}

inline void Board::place_pawns() {
	const int white_pawn_row = 1, black_pawn_row = 6;
	Tile white_pos{ white_pawn_row, 0 };
	Tile black_pos{ black_pawn_row, 0 };
	const char pawn = 'P';
	for (int col = 0; col < kNumRows; ++col) {
		white_pos.col = col;
		black_pos.col = col;
		set_tile(white_pos, piece_factory(Player::WHITE, white_pos, pawn));
		set_tile(black_pos, piece_factory(Player::BLACK, black_pos, pawn));
	}
}

inline void Board::place_pieces() {
	const char kPieceKey[]{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };  // Piece placements
	const int white_piece_row = 0, black_piece_row = 7;
	Tile white_pos{ white_piece_row, 0 };
	Tile black_pos{ black_piece_row, 0 };
	for (int col = 0; col < kNumCols; ++col) {
		white_pos.col = col;
		black_pos.col = col;
		set_tile(white_pos, piece_factory(Player::WHITE, white_pos, kPieceKey[col]));
		set_tile(black_pos, piece_factory(Player::BLACK, black_pos, kPieceKey[col]));
	}
}