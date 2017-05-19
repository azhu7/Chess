/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Singleton Chess Board
*/

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Linear_piece.h"

class King;
class View;

#include <cassert>
#include <iosfwd>
#include <memory>
#include <set>
#include <string>

// Pieces are stored in 1D 8x8 array of pointers to pieces.
// Starts as empty board. Controller loads board file to set the initial pieces.
// Provides functions for accessing and updating board.
// Reinforces rules for making moves.
class Board {
public:
    // Constants for castling, used by King
    static const int kLeftRookInitCol = 0;
    static const int kRightRookInitCol = 7;
    static const int kLeftRookCastledCol = 3;
    static const int kRightRookCastledCol = 5;
    static const int kKingLeftCastledCol = 2;
    static const int kKingRightCastledCol = 6;
    // Board size constants, used by View
    static const int kNum_rows = 8;
    static const int kNum_cols = 8;

    // Get Meyers Singleton Model reference
    static Board &get_instance();

    Board(const Board &) = delete;
    Board(Board &&) = delete;
    Board &operator=(const Board &) = delete;
    Board &operator=(Board &&) = delete;

    // Load Board from file
    void load_board(const std::string &board_name);

    // Return const Piece pointer at specified tile. Requires pos is valid tile.
    const std::shared_ptr<Piece> get_tile(Tile pos) const {
        assert(tile_in_bounds(pos));
        return board[pos];
    }

    // Return reference to Piece pointer at specified tile. Requires pos is 
    // valid tile.
    std::shared_ptr<Piece> &get_tile(Tile pos) {
        assert(tile_in_bounds(pos));
        return board[pos];
    }

    // Other getters and setters
    Player get_turn() const { return turn; }
    Tile get_last_en_passant_pos() const { return last_en_passant_pos; }
    void enpassant_occured() { en_passant = true; }
    void castle_occurred() { castle = true; };

    // Move piece to new tile. Requires old_pos and new_pos are valid tiles.
    void move(Tile old_pos, Tile new_pos);

    // View services
    // Attaching a View adds it to the container and causes it to be updated
    // with all current objects'location (or other state information).
    void attach(std::shared_ptr<View> view_ptr);
    // Detach the View by discarding the supplied pointer from the container of Views
    // - no updates sent to it thereafter.
    void detach(std::shared_ptr<View> view_ptr);
    // Notify the views about an piece's location
    void notify_position(const std::string &id, Tile pos);
    // Notify the views about an piece's new location
    void notify_move(const std::string &id, Tile old_pos, Tile new_pos);
    // Notify the views about an piece's removal. Used for en passants.
    void notify_remove(Tile pos);

private:
    std::shared_ptr<Piece> board[kNum_rows * kNum_cols];  // 1D 8x8 board
    std::set<std::shared_ptr<View>> views;  // Views subscribed to the Board
    Tile p1_king;  // Track each player's king to help with check detection
    Tile p2_king;
    Tile last_en_passant_pos;  // Track tile of pawn that moved two ranks last move. 
                               // {-1, -1} if none.
    Player turn = WHITE;  // White always goes first
    bool en_passant = false;  // True if current move is an en_passant
    bool castle = false;  // True if current move is a castle
    //Player checked_;  // Player whose King is under attack
                        //*** Check detection not yet implemented

    // Default ctor loads default board
    explicit Board();
    // Singleton should not be destructed by user
    ~Board() {}

    // Determine if tile is valid
    bool tile_in_bounds(Tile pos) const {
        int col = pos.col, row = pos.row;
        return col >= 0 && col < kNum_cols && row >= 0 && row < kNum_rows;
    }

    // Moves rook to correct castle position. Called by make_move().
    void castle_update_rook(Tile old_pos, Tile new_pos);

    // Promote pawn to new piece specified by user input
    void promote(Tile pos);

    // Determine if piece can be moved to new tile. Make sure piece moves
    // according to standard Chess rules.
    void validate_move(Tile old_pos, Tile new_pos) const;

    // Return true if any checks.
    //*** TODO     Accomplish by checking around King?
    bool detect_check() const;

    // Return true if checkmate
    bool detect_checkmate() const;
};

#endif  // !BOARD_H