/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for chess board
*/

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <cassert>
#include <iosfwd>

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

    explicit Board(std::istream &is);
    explicit Board();
    ~Board();

    // REQUIRES pos is valid tile
    // EFFECTS  Return const Piece pointer at specified tile
    const Piece *get_tile(const Tile &pos) const {
        assert(tile_in_bounds(pos));
        return board_[pos.row][pos.col];
    }

    // REQUIRES pos is valid tile
    // EFFECTS  Return reference to Piece pointer at specified tile
    Piece *&get_tile(const Tile &pos) {
        assert(tile_in_bounds(pos));
        return board_[pos.row][pos.col];
    }

    // EFFECTS  Determine if tile is valid
    bool tile_in_bounds(const Tile &pos) const {
        return pos.col >= 0 && (pos.col < kNumCols) &&
            (pos.row >= 0) && (pos.row < kNumRows);
    }

    // REQUIRES old_pos and new_pos are valid tiles
    // MODIFIES board_
    // EFFECTS  Move piece to new tile
    void move(const Tile &old_pos, const Tile &new_pos) {
        set_tile(new_pos, get_tile(old_pos));  // Move piece
        set_tile(old_pos, nullptr);  // old_pos is empty now
    }

    // EFFECTS  Pretty print the board
    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    // REQUIRES Valid initializing string format
    // MODIFIES board_
    // EFFECTS  Reads in, allocates, and places pieces on board_. Tiles read in
    //          from A8 to H8, A7 to H7, ..., A0 to H0.
    //              "1P" places a white Pawn at the current tile
    //              "--" indicates an empty tile
    template <size_t rows, size_t cols>
    friend std::istream &operator>>(std::istream &, Piece *(&board)[rows][cols]);

private:
    static const int kNumRows = 8;
    static const int kNumCols = 8;
    Piece *board_[kNumRows][kNumCols];  // 8x8 board of pointers to pieces

    // MODIFIES board_
    // EFFECTS  Fills board_ with nullptr
    void init_blank_board();

    // MODIFIES board_
    // EFFECTS  Places piece on board_ at specified tile
    void set_tile(const Tile &pos, Piece *piece) { get_tile(pos) = piece; }

    // MODIFIES board_
    // EFFECTS  Places pawns on board during initialization
    void place_pawns();

    // MODIFIES board_
    // EFFECTS  Places non-pawn pieces on board during initialization
    void place_pieces();
};

#endif  // !BOARD_H