#include "Board.h"

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Piece_factory.h"
#include "Queen.h"
#include "Rook.h"

#include <cassert>
#include <iostream>

using std::istream; using std::ostream; using std::cerr;
using std::is_base_of;

////////// BEGIN PUBLIC FUNCTIONS //////////

Board::Board(istream &is)
{
    // Fill board_ with nullptr
    init_blank_board();
    // Read in piece layout from input stream
    is >> board_;
}

Board::Board() {
    // Fill board_ with nullptr
    init_blank_board();
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
static void print_col_labels(ostream &os, int num_cols) {
    os << "    ";  // Front padding
    for (int col = 0; col < num_cols; ++col) {
        os << (char)('a' + col) << "  ";
    }
    os << '\n';
}

ostream &operator<<(ostream &os, const Board &board) {
    print_col_labels(os, board.kNumCols);  // Upper key

    // Print rows from bottom up
    for (int row = board.kNumRows - 1; row >= 0; --row) {
        Tile cur_tile{ row, 0 };
        os << row + 1 << " | ";  // LHS key
        for (int col = 0; col < board.kNumCols; ++col) {
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

    print_col_labels(os, board.kNumCols);  // Lower key
    return os;
}

template <size_t rows, size_t cols>
istream &operator>>(istream &is, Piece *(&board)[rows][cols]) {
    cerr << "Unimplemented!\n";
    return is;
}

////////// BEGIN PRIVATE FUNCTIONS //////////

void Board::init_blank_board() {
    // Initialize 8x8 array of nullptrs
    for (int i = 0; i < kNumRows; ++i) {
        for (int j = 0; j < kNumCols; ++j) {
            board_[i][j] = nullptr;
        }
    }
}

inline void Board::place_pawns() {
    const int white_pawn_row = 1, black_pawn_row = 6;
    Tile white_pos{ white_pawn_row, 0 };
    Tile black_pos{ black_pawn_row, 0 };
    for (int col = 0; col < kNumRows; ++col) {
        white_pos.col = col;
        black_pos.col = col;
        set_tile(white_pos, create_piece(Player::WHITE, white_pos, Piece::P));
        set_tile(black_pos, create_piece(Player::BLACK, black_pos, Piece::P));
    }
}

inline void Board::place_pieces() {
    // Piece placements
    const int white_piece_row = 0, black_piece_row = 7;
    const Piece::PieceType kPieceKey[kNumCols]{ Piece::R, Piece::N, Piece::B,
        Piece::Q, Piece::K, Piece::B, Piece::N, Piece::R };
    Tile white_pos{ white_piece_row, 0 };
    Tile black_pos{ black_piece_row, 0 };
    for (int col = 0; col < kNumCols; ++col) {
        white_pos.col = col;
        black_pos.col = col;
        set_tile(white_pos, create_piece(Player::WHITE, white_pos, kPieceKey[col]));
        set_tile(black_pos, create_piece(Player::BLACK, black_pos, kPieceKey[col]));
    }
}