/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Chess board
*/

#include "Board.h"

#include "King.h"
#include "Pawn.h"
#include "Piece.h"
#include "Piece_factory.h"
#include "Rook.h"
#include "Utility.h"
#include "View.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>

using std::fill;
using std::ifstream;
using std::shared_ptr; using std::dynamic_pointer_cast; using std::static_pointer_cast;
using std::bind; using namespace std::placeholders;
using std::cout; using std::cin;
using std::bad_alloc; using std::exception;
using std::string;

/*
Board public members
*/

// Return Singleton Board
Board &Board::get_instance() {
    static Board b;
    return b;
}

// Load Board from file
void Board::load_board(const string &board_name) {
    ifstream ifs{ board_name };
    if (!ifs.is_open())
        throw Error{ "Could not open Board file" };

    for (int i = kNum_rows - 1; i >= 0; --i) {
        for (int j = 0; j < kNum_cols; ++j) {
            char player;
            char piece_type;
            if (!(ifs >> player >> piece_type))
                throw Error{ "Error reading in Board" };
            Tile cur_tile{ i, j };
            if (player == '-')
                board[cur_tile] = nullptr;
            else {
                Player p = player == '1' ? WHITE : BLACK;
                board[cur_tile] = create_piece(p, cur_tile, piece_type);
                notify_position(board[cur_tile]->get_id(), cur_tile);
            }
        }
    }
}

// Move piece to new tile. Requires old_pos and new_pos are valid tiles.
void Board::move(Tile old_pos, Tile new_pos) {
    validate_move(old_pos, new_pos);  // Run validity checks on move

    // Account for en passant capture
    if (en_passant) {
        board[last_en_passant_pos] = nullptr;
        notify_remove(last_en_passant_pos);
        en_passant = false;
    }
    // Account for castle
    else if (castle) {
        castle_update_rook(old_pos, new_pos);
        castle = false;
    }
    last_en_passant_pos = Tile{};  // Reset en passant tile

    shared_ptr<Piece> cur_piece = board[old_pos];
    board[new_pos] = board[old_pos];  // Move piece
    board[old_pos] = nullptr;  // old_pos is empty now
    cur_piece->set_pos(new_pos);  // Update piece coordinates
    cur_piece->set_moved();  // Needed by Rook and King for castling
    notify_move(cur_piece->get_id(), old_pos, new_pos);
    
    // Brief switch-on-type logic to update tracking variables
    if (dynamic_pointer_cast<Pawn>(cur_piece)) {
        if (abs(new_pos.row - old_pos.row) == 2) {
            // Note that pawn is moving two tiles. Needed for possible en passant.
            last_en_passant_pos = new_pos;
        }
        else if (new_pos.row == 0 || new_pos.row == kNum_rows - 1) {
            // Promotion if Pawn reached end
            promote(new_pos);
        }
    }
        
    else if (dynamic_pointer_cast<King>(cur_piece)) {
        // Update King position
        turn == WHITE ? p1_king = cur_piece->get_pos() : p2_king = cur_piece->get_pos();
    }

    turn = turn == WHITE ? BLACK : WHITE;  // Switch turns upon successful move
}

// Attaching a View adds it to the container and causes it to be updated
// with all current objects'location (or other state information).
void Board::attach(shared_ptr<View> view_ptr) {
    views.emplace(view_ptr);
    // Update new view
    for_each(board, board + kNum_rows * kNum_cols, 
        [this, view_ptr](shared_ptr<Piece> p) {
        if (p)
            view_ptr->update_position(p->get_id(), p->get_pos());
    });
}

// Detach the View by discarding the supplied pointer from the container of Views
// - no updates sent to it thereafter.
void Board::detach(shared_ptr<View> view_ptr) {
    views.erase(view_ptr);
}

// Notify the views about an piece's location
void Board::notify_position(const string &id, Tile pos) {
    for_each(views.cbegin(), views.cend(),
        bind(&View::update_position, _1, id, pos));
}

// Notify the views about an piece's new location
void Board::notify_move(const string &id, Tile old_pos, Tile new_pos) {
    for_each(views.cbegin(), views.cend(),
        bind(&View::update_move, _1, id, old_pos, new_pos));
}

// Notify the views about a piece's removal. Used for en passants.
void Board::notify_remove(Tile pos) {
    for_each(views.cbegin(), views.cend(),
        bind(&View::update_remove, _1, pos));
}

/*
Board private members
*/

// Default ctor loads default board
//*** How to get King position for non-default board? Just set when loading board! Don't have defaults here.
Board::Board()
    : p1_king{ King::P1_KING_START }, p2_king{ King::P2_KING_START } {}

// Moves rook to correct castle position. Called by make_move().
void Board::castle_update_rook(Tile old_pos, Tile new_pos) {
    // lambda to move rook to castled position
    static auto move_rook_to_castled = [&](int rook_col,
        int castled_col) {
        const Tile rook_pos{ old_pos.row, rook_col };
        const Tile castled_pos{ old_pos.row, castled_col };
        shared_ptr<Rook> temp_rook = static_pointer_cast<Rook>(board[rook_pos]);
        board[castled_pos] = board[rook_pos];  // Move piece
        board[rook_pos] = nullptr;  // old_pos is empty now
        temp_rook->set_pos(castled_pos);  // Update Rook's pos
        temp_rook->set_moved();
        notify_move(temp_rook->get_id(), rook_pos, castled_pos);
    };

    if (new_pos.col > old_pos.col)
        // Castle to the right. Adjust right rook.
        move_rook_to_castled(kRightRookInitCol, kRightRookCastledCol);
    else
        // Castle to the left. Adjust left rook.
        move_rook_to_castled(kLeftRookInitCol, kLeftRookCastledCol);
}

// Promote pawn to new piece specified by user input
void Board::promote(Tile pos) {
    cout << "What would you like to promote to? (N,B,R,Q): ";
    char piece_id;
    while (true) {
        cin >> piece_id;
        switch (piece_id) {
        case 'P': {
            cout << "Can't promote to pawn!\n";
            break;
        }
        case 'K': {
            cout << "Can't promote to king!\n";
            break;
        }
        default: {
            try {
                // Attempt to create piece
                shared_ptr<Piece> new_piece = create_piece(turn, pos, piece_id);
                board[pos] = new_piece;
                notify_position(new_piece->get_id(), pos);
                skip_line();  // Skip remainder of input line, namely the \n.
                return;
            }
            catch (Error &e) {
                cout << e.what() << '\n';
            }
        }
        }
        cout << "Try again: ";
    }
}

// Determine if piece can be moved to new tile. Make sure piece moves
// according to standard Chess rules.
void Board::validate_move(Tile old_pos, Tile new_pos) const {
    if (!(tile_in_bounds(new_pos) && tile_in_bounds(old_pos)))
        throw Error{ "Input tile is out of bounds!\n" };

    const shared_ptr<Piece> cur_piece = board[old_pos];
    const shared_ptr<Piece> new_tile = board[new_pos];
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