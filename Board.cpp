#include "Board.h"
#include "Player.h"
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

const int kNumRows = 8;
const int kNumCols = 8;

void print_col_labels(std::ostream &os);
std::ostream &operator<<(std::ostream &os, const Board &board);

////////// BEGIN PRIVATE FUNCTIONS //////////

inline Piece *Board::piece_factory(const Player color, const int col,
	const int row, const char type) const {
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
	const int white_pawn_row = 1, black_pawn_row = 6;
	const char pawn = 'P';
	for (int col = 0; col < kNumRows; ++col) {
		board_[white_pawn_row][col] = piece_factory(Player::WHITE, col, white_pawn_row, pawn);
		board_[black_pawn_row][col] = piece_factory(Player::BLACK, col, black_pawn_row, pawn);
	}
}

inline void Board::place_pieces() {
	const char kPieceKey[]{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };  // Piece placements
	const int white_row = 0, black_row = 7;
	for (int col = 0; col < kNumCols; ++col) {
		board_[white_row][col] = piece_factory(Player::WHITE, col, white_row, kPieceKey[col]);
		board_[black_row][col] = piece_factory(Player::BLACK, col, black_row, kPieceKey[col]);
	}
}

inline void Board::switch_turns() {
	turn_ = turn_ == Player::WHITE ? Player::BLACK : Player::WHITE;
}

inline void Board::swap(Piece *&p1, Piece *&p2) {
	Piece *temp = p2;
	p2 = p1;
	p1 = temp;
}

inline bool Board::tile_in_bounds(const int col_in, const int row_in) const {
	return col_in >= 0 && (col_in < kNumCols) &&
		(row_in >= 0) && (row_in < kNumRows);
}

bool Board::path_is_clear(const int old_col, const int old_row,
	const int new_col, const int new_row) const {
	return false;
}

bool Board::valid_move(const int old_col, const int old_row,
	const int new_col, const int new_row) const {
	if (!(tile_in_bounds(new_col, new_row) && tile_in_bounds(old_col, old_row))) {
		std::cout << "Input tile is out of bounds\n";
		return false;
	}
	Piece *cur_piece = get_tile(old_col, old_row);
	Piece *new_tile = get_tile(new_col, new_row);

	if (!cur_piece) {
		return false;  // Player selected empty tile
	}

	// Player move their own piece
	bool correct_team = cur_piece->get_player() == turn_;
	// Okay placement
	bool placement = cur_piece->valid_placement(new_col, new_row);
	// Check Pawn special case
	if (cur_piece->get_type() == 'P') {
		Piece *&target_tile = get_tile(new_col, new_row);
		// If vertical move, make sure target spot is empty
		if (placement) {
			placement = !target_tile;
		}
		else {
			// Otherwise, check if pawn is capturing an enemy piece
			Pawn *temp_pawn = static_cast<Pawn *>(cur_piece);
			placement = temp_pawn->valid_capture(new_col, new_row) &&
				target_tile && target_tile->get_player() != turn_;
		}
	}
	// Can't move onto own piece
	bool same_team = new_tile ? new_tile->get_player() == cur_piece->get_player() : false;

	return correct_team && placement && !same_team;
}


////////// BEGIN PUBLIC FUNCTIONS //////////

Board::Board()
	: turn_{ Player::WHITE } {
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

inline Piece *&Board::get_tile(const int col, const int row) const {
	// Check in-bounds requirement
	assert(col >= 0 && col < kNumCols);
	assert(row >= 0 && row < kNumRows);
	return board_[row][col];
}

std::string Board::get_current_player() const {
	return player_to_string(turn_);
}

bool Board::move(const int old_col, const int old_row,
	const int new_col, const int new_row) {
	if (!valid_move(old_col, old_row, new_col, new_row)) {
		std::cout << ">>> Invalid move. Try again! <<<\n";
		return false;  // Unsuccessful move
	}

	Piece *&cur_piece = get_tile(old_col, old_row);
	Piece *&target_tile = get_tile(new_col, new_row);
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
			Piece *cur_piece = board.get_tile(col, row);
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