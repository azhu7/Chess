/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Chess board
*/

#include "Board.h"

#include "Piece.h"
#include "Piece_factory.h"

//*** TODO: Get rid of these later
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include <cassert>
#include <iostream>

using std::istream; using std::ostream; using std::cerr;
using std::is_base_of;

/*
Board public members
*/

// Return Singleton Board
Board &Board::get_instance() {
    static Board b;
    return b;
}

// EFFECTS  Helper function for printing out column labels
static void print_col_labels(ostream &os, int num_cols) {
    os << "    ";  // Front padding
    for (int col = 0; col < num_cols; ++col) {
        os << (char)('a' + col) << "  ";
    }
    os << '\n';
}

bool Board::move(Tile old_pos, Tile new_pos) {
    if (!valid_move(old_pos, new_pos)) {
        cerr << ">>> Invalid move. Try again! <<<\n";
        return false;
    }

    Piece *cur_piece = get_tile(old_pos);
    if (Piece *&target_tile = get_tile(new_pos)) {
        // Capture enemy piece
        assert(target_tile->get_player() != turn);  // Make sure enemy piece
        delete target_tile;
        target_tile = nullptr;
    }

    // Account for en passant capture
    if (en_passant)
        capture_en_passant_pawn();
    last_en_passant_pos = Tile{};  // Reset en passant tile

    switch (cur_piece->get_type()) {
    case Piece::P: {
        // Check if pawn is moving two tiles. Needed for possible en passant.
        bool two_rank_move = abs(new_pos.row - old_pos.row) == 2 && new_pos.col == old_pos.col;
        if (two_rank_move)
            last_en_passant_pos = new_pos;
        break;
    }
    case Piece::R: {
        Rook *temp_rook = static_cast<Rook *>(cur_piece);
        temp_rook->set_moved();  // Rook has moved (can no longer castle on this side)
        break;
    }
    case Piece::K: {
        King *temp_king = static_cast<King *>(cur_piece);
        //*** RESTORE THIS CODE WHEN PORTING TO KING
        //if (valid_castle(temp_king, new_pos))
        //    castle_update_rook(old_pos, new_pos);  // On castle, update rook as well
        temp_king->set_moved();  // King has moved (can no longer castle)
        set_king_pos(temp_king);
        break;
    }
    case Piece::B: case Piece::N: case Piece::Q:
        // No special case for Bishops, Knights, and Queens
        break;
    }  // switch

    en_passant = false;
    cur_piece->set_pos(new_pos);  // Update piece coordinates
    get_tile(new_pos) = get_tile(old_pos);  // Move piece
    get_tile(old_pos) = nullptr;  // old_pos is empty now
    switch_turns();  // Switch turns upon successful move
    return true;
}

//*** TODO: Consider making a View class for this
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

/*
Board private members
*/

Board::Board()
    : p1_king{ King::P1_KING_START }, p2_king{ King::P2_KING_START }, 
    turn{ Player::WHITE }, en_passant{ false } {
    // Fill board with nullptr
    init_blank_board();
    // Place all pieces onto board. Dynamic pieces will be deallocated as they are
    // captures and remaining pieces deallocated by destructor.
    place_pawns();
    place_pieces();
}

Board::Board(istream &is) {
    // Fill board with nullptr
    init_blank_board();
    // Read in piece layout from input stream
    is >> board;
}

Board::~Board() {
    for (auto &row : board) {
        for (auto piece : row) {
            delete piece;
            piece = nullptr;
        }
    }
}

void Board::init_blank_board() {
    // Initialize 8x8 array of nullptrs
    for (int i = 0; i < kNumRows; ++i) {
        for (int j = 0; j < kNumCols; ++j) {
            board[i][j] = nullptr;
        }
    }
}

void Board::place_pawns() {
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

void Board::place_pieces() {
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

void Board::capture_en_passant_pawn() {
    Piece *&target_tile = get_tile(last_en_passant_pos);
    delete target_tile;
    target_tile = nullptr;
}

void Board::set_king_pos(King *king) {
    if (king->get_player() == Player::WHITE)
        p1_king = king->get_pos();
    else
        p2_king = king->get_pos();
}

void Board::castle_update_rook(Tile old_pos, Tile new_pos) {
    // lambda to move rook to castled position
    static auto move_rook_to_castled = [&](int rook_col,
        int castled_col) {
        const Tile rook_pos{ old_pos.row, rook_col };
        const Tile castled_pos{ old_pos.row, castled_col };
        Rook *temp_rook = static_cast<Rook *>(get_tile(rook_pos));
        get_tile(rook_pos) = get_tile(castled_pos);  // Move piece
        get_tile(castled_pos) = nullptr;  // old_pos is empty now
        temp_rook->set_moved();
    };

    if (new_pos.col > old_pos.col)
        // Castle to the right. Adjust right rook.
        move_rook_to_castled(Board::kRightRookInitCol, Board::kRightRookCastledCol);
    else
        // Castle to the left. Adjust left rook.
        move_rook_to_castled(Board::kLeftRookInitCol, Board::kLeftRookCastledCol);
}

bool Board::valid_move(Tile old_pos, Tile new_pos) const {
    if (!(tile_in_bounds(new_pos) && tile_in_bounds(old_pos))) {
        cerr << "Input tile is out of bounds\n";
        return false;
    }

    const Piece *cur_piece = get_tile(old_pos);
    const Piece *new_tile = get_tile(new_pos);
    if (!cur_piece)
        return false;  // Player selected empty tile

                       // Players can only move their own pieces
    if (cur_piece->get_player() != turn) {
        cerr << "Can't move enemy piece\n";
        return false;
    }

    // Can't move onto own piece
    bool capture_own_piece = new_tile ? new_tile->get_player() ==
        cur_piece->get_player() : false;
    if (capture_own_piece) {
        cerr << "Can't capture own piece\n";
        return false;
    }

    return cur_piece->valid_move(new_pos);
    //*** TODO: Checks on own piece = invalid; checks on enemy piece = update checked_
}