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

#include <cassert>
#include <iosfwd>
#include <memory>
#include <string>

// Simple board: pieces are stored in 8x8 array of pointers to pieces.
// Provides functions for accessing and updating board.
// Reinforces rules for making moves.
class Board {
public:
    // Constants for castling
    static const int kLeftRookInitCol = 0;
    static const int kRightRookInitCol = 7;
    static const int kLeftRookCastledCol = 3;
    static const int kRightRookCastledCol = 5;
    static const int kKingLeftCastledCol = 2;
    static const int kKingRightCastledCol = 6;

    // Get Meyers Singleton Model reference
    static Board &get_instance();

    Board(const Board &) = delete;
    Board(Board &&) = delete;
    Board &operator=(const Board &) = delete;
    Board &operator=(Board &&) = delete;

    // Return const Piece pointer at specified tile. Requires pos is valid tile.
    const std::shared_ptr<Piece> get_tile(Tile pos) const {
        assert(tile_in_bounds(pos));
        return board[pos.row][pos.col];
    }

    // Return reference to Piece pointer at specified tile. Requires pos is 
    // valid tile.
    std::shared_ptr<Piece> &get_tile(Tile pos) {
        assert(tile_in_bounds(pos));
        return board[pos.row][pos.col];
    }

    // Other getters and setters
    Player get_turn() const { return turn; }
    Tile get_last_en_passant_pos() const { return last_en_passant_pos; }
    void enpassant_occured() { en_passant = true; }
    void castle_occurred() { castle = true; };

    // Move piece to new tile. Requires old_pos and new_pos are valid tiles.
    void move(Tile old_pos, Tile new_pos);

    // Pretty print the board
    friend std::ostream &operator<<(std::ostream &os, const Board &board);

private:
    static const int kNumRows = 8;
    static const int kNumCols = 8;
    std::shared_ptr<Piece> board[kNumRows][kNumCols];  // 8x8 board of pointers to pieces
    Tile p1_king;  // Track each player's king to help with check detection
    Tile p2_king;
    Tile last_en_passant_pos;  // Track tile of pawn that moved two ranks last move. 
                               // {-1, -1} if none.
    Player turn = Player::WHITE;  // White always goes first
    bool en_passant = false;  // True if current move is an en_passant
    bool castle = false;  // True if current move is a castle
    //Player checked_;  // Player whose King is under attack
                        //*** Check detection not yet implemented

    // Default ctor loads default board
    explicit Board();
    // Singleton should not be destructed by user
    ~Board() {}

    // Load Board from file
    void load_board(const std::string &board_name);

    // Fills board with nullptr
    //*** TODO: Don't need this?
    void clear() noexcept;

    // Determine if tile is valid
    bool tile_in_bounds(Tile pos) const {
        int col = pos.col, row = pos.row;
        return col >= 0 && col < kNumCols && row >= 0 && row < kNumRows;
    }

    // Places piece on board at specified tile
    void set_tile(Tile pos, std::shared_ptr<Piece> piece) { 
        board[pos.row][pos.col] = piece;
    }

    // Updates whose turn it is. Called by make_move()
    void switch_turns() {
        turn = turn == Player::WHITE ? Player::BLACK : Player::WHITE;
    }

    //*** Ported from MoveMaker

    // Moves rook to correct castle position. Called by make_move()
    void castle_update_rook(Tile old_pos, Tile new_pos);

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