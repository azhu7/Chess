/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Pawn piece
*/

#include "Pawn.h"

#include <cmath>

using std::abs;

/*
Pawn public members
*/

bool Pawn::valid_capture_placement(const Tile &new_pos) const {
    const int row_diff = new_pos.row - get_row();
    const int col_abs_diff = abs(new_pos.col - get_col());

    // Valid if move 1 tile diagonally
    // White pawn must capture up one col. Black pawn capture down one col
    return col_abs_diff == 1 && (get_player() == Player::WHITE ? row_diff == 1 : 
        row_diff == -1);
}

bool Pawn::valid_placement(const Tile &new_pos) const {
    const int row_diff = new_pos.row - get_row();
    const int col_diff = new_pos.col - get_col();

    // Pawns cannot move left/right except to capture
    // (checked by Pawn::valid_capture_placement())
    if (col_diff)
        return false;

    // Case 1: white pawn
    if (get_player() == Player::WHITE) {
        // First move can go 1 or 2 tiles up
        if (get_row() == kWhitePawnStart)
            return (row_diff == 1) || (row_diff == 2);
        // Otherwise, can only go 1 tile up
        return row_diff == 1;
    }
    // Case 2: black pawn
    // First move can go 1 or 2 tiles down
    if (get_row() == kBlackPawnStart)
        return (row_diff == -1 || row_diff == -2);
    // Otherwise, can only go 1 tile down
    return row_diff == -1;
}