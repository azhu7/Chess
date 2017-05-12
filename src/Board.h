/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Linear_piece.h"

class King;

#include <cassert>
#include <iosfwd>
#include <string>

// Simple board: pieces are stored in 8x8 array of pointers to pieces.
// Provides functions for accessing and updating board.
// MoveMaker wrapper required to reinforce rules for making certain moves.
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

    // REQUIRES pos is valid tile
    // EFFECTS  Return const Piece pointer at specified tile
    const Piece *get_tile(Tile pos) const {
        assert(tile_in_bounds(pos));
        return board[pos.row][pos.col];
    }

    // REQUIRES pos is valid tile
    // EFFECTS  Return reference to Piece pointer at specified tile
    Piece *&get_tile(Tile pos) {
        assert(tile_in_bounds(pos));
        return board[pos.row][pos.col];
    }

    Player get_turn() const { return turn; }
    Tile get_last_en_passant_pos() const { return last_en_passant_pos; }
    void enpassant_occured() { en_passant = true; }
    void castle_occurred() { castle = true; };

    // EFFECTS  Determine if tile is valid
    bool tile_in_bounds(Tile pos) const {
        return pos.col >= 0 && (pos.col < kNumCols) &&
            (pos.row >= 0) && (pos.row < kNumRows);
    }

    // REQUIRES old_pos and new_pos are valid tiles
    // MODIFIES board
    // EFFECTS  Move piece to new tile
    bool move(Tile old_pos, Tile new_pos);

    // EFFECTS  Pretty print the board
    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    // REQUIRES Valid initializing string format
    // MODIFIES board
    // EFFECTS  Reads in, allocates, and places pieces on board. Tiles read in
    //          from A8 to H8, A7 to H7, ..., A0 to H0.
    //              "1P" places a white Pawn at the current tile
    //              "--" indicates an empty tile
    template <size_t rows, size_t cols>
    friend std::istream &operator>>(std::istream &, Piece *(&board)[rows][cols]);

private:
    static const int kNumRows = 8;
    static const int kNumCols = 8;
    Piece *board[kNumRows][kNumCols];  // 8x8 board of pointers to pieces
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
    ~Board();

    // MODIFIES board
    // EFFECTS  Fills board with nullptr
    void clear() noexcept;

    // MODIFIES board
    // EFFECTS  Places piece on board at specified tile
    void set_tile(Tile pos, Piece *piece) { get_tile(pos) = piece; }

    // Load Board from file
    void load_board(const std::string &board_name);

    // MODIFIES turn_
    // EFFECTS  Updates whose turn it is. Called by make_move()
    void switch_turns() {
        turn = turn == Player::WHITE ? Player::BLACK : Player::WHITE;
    }

    //*** Ported from MoveMaker

    // MODIFIES board_
    // EFFECTS  Remove en passant pawn from board_
    void capture_en_passant_pawn();

    // MODIFIES p1_king or p2_king depending on which player king belongs to
    // EFFECTS  Update the king's position as tracked by MoveMaker
    void set_king_pos(King *king);

    // MODIFIES rook, board_
    // EFFECTS  Moves rook to correct castle position. Called by make_move()
    void castle_update_rook(Tile old_pos, Tile new_pos);

    // EFFECTS  Determine if piece can be moved to new tile.
    //          Make sure piece moves according to Chess rules.
    bool valid_move(Tile old_pos, Tile new_pos) const;

    // EFFECTS  Upon a successful move, detect any checks
    //*** TODO     Accomplish by checking around King?
    bool detect_check() const;

    // EFFECTS  Upon a check, detect checkmate
    bool detect_checkmate() const;
};

#endif  // !BOARD_H