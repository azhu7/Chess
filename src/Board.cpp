/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Chess board
*/

#include "Board.h"

#include "Piece.h"
#include "Piece_factory.h"

//*** TODO: Get rid of these later
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Utility.h"

#include <cassert>
#include <iostream>
#include <fstream>

using std::istream; using std::ostream; using std::cerr;
using std::ifstream;
using std::shared_ptr; using std::dynamic_pointer_cast; using std::static_pointer_cast;
using std::string;

// Helpers
static void print_col_labels(ostream &os, int num_cols);

/*
Board public members
*/

// Return Singleton Board
Board &Board::get_instance() {
    static Board b;
    return b;
}

//*** TODO: Replace bool return with void. Throw exception on error.
void Board::move(Tile old_pos, Tile new_pos) {
    validate_move(old_pos, new_pos);

    shared_ptr<Piece> cur_piece = get_tile(old_pos);
    if (shared_ptr<Piece> &target_tile = get_tile(new_pos)) {
        // Capture enemy piece
        assert(target_tile->get_player() != turn);  // Make sure enemy piece
        target_tile = nullptr;
    }

    // Account for en passant capture
    if (en_passant) {
        get_tile(last_en_passant_pos) = nullptr;
        en_passant = false;
    }
    // Account for castle
    else if (castle) {
        castle_update_rook(old_pos, new_pos);
        castle = false;
    }
    last_en_passant_pos = Tile{};  // Reset en passant tile

    get_tile(new_pos) = get_tile(old_pos);  // Move piece
    get_tile(old_pos) = nullptr;  // old_pos is empty now
    cur_piece->set_pos(new_pos);  // Update piece coordinates
    
    // Brief switch-on-type logic to update tracking variables
    if (dynamic_pointer_cast<Pawn>(cur_piece) && abs(new_pos.row - old_pos.row) == 2)
        // Note that pawn is moving two tiles. Needed for possible en passant.
        last_en_passant_pos = new_pos;
    else if (shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(cur_piece))
        rook->set_moved();  // Rook has moved (can no longer castle on this side)
    else if (shared_ptr<King> king = dynamic_pointer_cast<King>(cur_piece)) {
        king->set_moved();  // King has moved (can no longer castle)
        // Update King position
        turn == Player::WHITE ? p1_king = king->get_pos() : p2_king = king->get_pos();
    }

    switch_turns();  // Switch turns upon successful move
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
            const shared_ptr<Piece> cur_piece = board.get_tile(cur_tile);
            if (cur_piece) {
                os << *cur_piece;
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

// Helper function for printing out column labels
void print_col_labels(ostream &os, int num_cols) {
    os << "    ";  // Front padding
    for (int col = 0; col < num_cols; ++col) {
        os << (char)('a' + col) << "  ";
    }
    os << '\n';
}

/*
Board private members
*/

// Default ctor loads default board
Board::Board()
    : p1_king{ King::P1_KING_START }, p2_king{ King::P2_KING_START } {
    load_board("default_board.txt");
}

// Load Board from file
void Board::load_board(const string &board_name) {
    ifstream ifs{ board_name };
    if (!ifs)
        throw Error{ "Could not open Board file" };

    for (int i = kNumRows - 1; i >= 0; --i) {
        for (int j = 0; j < kNumCols; ++j) {
            char player;
            char piece_type;
            if (!(ifs >> player >> piece_type))
                //*** TODO: Test that this doesn't leak b/c singleton
                throw Error{ "Error reading in Board" };
            if (player == '-')
                board[i][j] = nullptr;
            else {
                Player p = player == '1' ? Player::WHITE : Player::BLACK;
                board[i][j] = create_piece(p, Tile{ i, j }, piece_type);
            }
        }
    }
}

void Board::castle_update_rook(Tile old_pos, Tile new_pos) {
    // lambda to move rook to castled position
    static auto move_rook_to_castled = [&](int rook_col,
        int castled_col) {
        const Tile rook_pos{ old_pos.row, rook_col };
        const Tile castled_pos{ old_pos.row, castled_col };
        shared_ptr<Rook> temp_rook = static_pointer_cast<Rook>(get_tile(rook_pos));
        get_tile(castled_pos) = get_tile(rook_pos);  // Move piece
        get_tile(rook_pos) = nullptr;  // old_pos is empty now
        temp_rook->set_pos(castled_pos);  // Update Rook's pos
        temp_rook->set_moved();
    };

    if (new_pos.col > old_pos.col)
        // Castle to the right. Adjust right rook.
        move_rook_to_castled(kRightRookInitCol, kRightRookCastledCol);
    else
        // Castle to the left. Adjust left rook.
        move_rook_to_castled(kLeftRookInitCol, kLeftRookCastledCol);
}

void Board::validate_move(Tile old_pos, Tile new_pos) const {
    if (!(tile_in_bounds(new_pos) && tile_in_bounds(old_pos)))
        throw Error{ "Input tile is out of bounds!\n" };

    const shared_ptr<Piece> cur_piece = get_tile(old_pos);
    const shared_ptr<Piece> new_tile = get_tile(new_pos);
    // Player selected empty tile
    if (!cur_piece)
        throw Error{ "No piece selected!\n" };
    // Players can only move their own pieces
    if (cur_piece->get_player() != turn)
        throw Error{ "Can't move enemy piece!\n" };
    // Can't move onto own piece
    bool capture_own_piece = new_tile ? new_tile->get_player() ==
        cur_piece->get_player() : false;
    if (capture_own_piece)
        throw Error{ "Can't capture own piece!\n" };

    if (!cur_piece->valid_move(new_pos))
        throw Error{ "Can't move specified piece there!\n" };
    //*** TODO: Check if own King is being attacked. If so, then invalid.
    //*** Check if enemy king is being attacked. If so, update checked_.
}