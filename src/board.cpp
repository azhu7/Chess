#include "../include/board.h"
#include "../include/piece.h"
#include "../include/pawn.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/king.h"
#include <iostream>
#include <cassert>

////////// BEGIN PUBLIC FUNCTIONS //////////

Board::Board(std::istream &is)
{
	// Fill board_ with nullptr
	init_board();

	// Read in piece layout from input stream
	is >> board_;
}

Board::Board() {
	// Fill board_ with nullptr
	init_board();

	// Place all pieces onto board. Dynamic pieces will be deallocated as they are
	// captures and remaining pieces deallocated by destructor.
	place_pawns();
	place_pieces();
}

Board::~Board() {
	for (auto &row : board_) {
		for (auto piece : row) {
			delete piece;
			piece = nullptr;
		}
	}
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
	print_col_labels(os);  // Upper key

	// Print rows from bottom up
	for (int row = kNumRows - 1; row >= 0; --row) {
		Tile cur_tile{ row, 0 };
		os << row + 1 << " | ";  // LHS key
		for (int col = 0; col < kNumCols; ++col) {
			cur_tile.col = col;
			const Piece *cur_piece = board.get_tile(cur_tile);
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

template <size_t rows, size_t cols>
std::istream &operator>>(std::istream &is, Piece *(&board)[rows][cols]) {
	std::cout << "Unimplemented!\n";
	return is;
}

////////// BEGIN PRIVATE FUNCTIONS //////////

void Board::init_board() {
	// Initialize 8x8 array of nullptrs
	for (int i = 0; i < kNumRows; ++i) {
		for (int j = 0; j < kNumCols; ++j) {
			board_[i][j] = nullptr;
		}
	}
}

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