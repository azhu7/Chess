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
#include <algorithm>
#include <string>

const int kNumRows = 8;
const int kNumCols = 8;

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

inline void Board::switch_turns() {
	turn_ = turn_ == Player::WHITE ? Player::BLACK : Player::WHITE;
}

inline void Board::swap(Piece *&p1, Piece *&p2) {
	Piece *temp = p2;
	p2 = p1;
	p1 = temp;
}

inline bool Board::tile_in_bounds(const Tile &pos) const {
	return pos.col >= 0 && (pos.col < kNumCols) &&
		(pos.row >= 0) && (pos.row < kNumRows);
}

bool Board::valid_move(const Tile &old_pos, const Tile &new_pos) const {
	if (!(tile_in_bounds(new_pos) && tile_in_bounds(old_pos))) {
		std::cout << "Input tile is out of bounds\n";
		return false;
	}
	Piece *cur_piece = get_tile(old_pos);
	Piece *new_tile = get_tile(new_pos);

	if (!cur_piece) {
		return false;  // Player selected empty tile
	}

	// Player move their own piece
	bool correct_team = cur_piece->get_player() == turn_;
	// Okay placement
	bool placement = cur_piece->valid_placement(new_pos);
	// Check Pawn special case
	if (cur_piece->get_type() == 'P') {
		Piece *&target_tile = get_tile(new_pos);
		// If vertical move, make sure target spot is empty
		if (placement) {
			placement = !target_tile;
		}
		else {
			// Otherwise, check if pawn is capturing an enemy piece
			Pawn *temp_pawn = static_cast<Pawn *>(cur_piece);
			placement = temp_pawn->valid_capture(new_pos) &&
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

inline Piece *&Board::get_tile(const Tile &pos) const {
	// Check in-bounds requirement
	assert(pos.col >= 0 && pos.col < kNumCols);
	assert(pos.row >= 0 && pos.row < kNumRows);
	return board_[pos.row][pos.col];
}

inline void Board::set_tile(const Tile & pos, Piece *piece)
{
	board_[pos.row][pos.col] = piece;
}

Player Board::get_current_player() const {
	return turn_;
}

bool Board::move(const Tile &old_pos, const Tile &new_pos) {
	if (!valid_move(old_pos, new_pos)) {
		std::cout << ">>> Invalid move. Try again! <<<\n";
		return false;  // Unsuccessful move
	}

	Piece *&cur_piece = get_tile(old_pos);
	Piece *&target_tile = get_tile(new_pos);
	if (target_tile) {
		// Capture enemy piece
		assert(target_tile->get_player() != turn_);  // Make sure enemy piece
		delete target_tile;
		target_tile = nullptr;
	}
	cur_piece->set_coords(new_pos);  // Update piece coordinates
	swap(get_tile(old_pos), get_tile(new_pos));  // Move piece
	assert(!get_tile(old_pos));  // Old tile should contain nullptr
	switch_turns();  // Switch turns upon successful move
	return true;
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