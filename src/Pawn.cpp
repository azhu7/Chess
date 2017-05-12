/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Pawn piece
*/

#include "Pawn.h"

#include "Board.h"

#include <cmath>

/*
Pawn public members
*/

// Inherited from Piece base class
bool Pawn::valid_physical_placement(Tile new_pos) const {
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
bool Pawn::additional_placement_checks(bool valid_physical_placement, Tile new_pos) const {
    Piece *target_tile = Board::get_instance().get_tile(new_pos);
    bool okay_placement;
    if (valid_physical_placement) {
        // Vertical move: make sure target path is empty
        okay_placement = !target_tile;
        if (abs(new_pos.row - get_pos().row) == 2) {
            // Check tile one above/below pawn
            Tile one_tile_away{ (get_pos().row + new_pos.row) / 2, get_pos().col };
            // Both tiles clear
            okay_placement = okay_placement && !Board::get_instance().get_tile(one_tile_away);
        }
    }
    else {
        // Check if pawn is capturing an enemy piece
        Tile en_passant_tile{ get_pos().row, new_pos.col };
        // Check if Pawn is capturing a Pawn that just moved two tiles
        bool possible_en_passant =
            Board::get_instance().get_last_en_passant_pos() == en_passant_tile;
        // Captured a piece if target tile contains enemy piece OR valid en passant
        bool captured_a_piece = (target_tile && target_tile->get_player() != get_player()) ||
            possible_en_passant;
        okay_placement = valid_capture_placement(new_pos) && captured_a_piece;
        // Notify Board that this move was an en passant
        if (okay_placement && possible_en_passant)
            Board::get_instance().enpassant_occured();
    }
    return okay_placement;
}

// Determine if move is valid capture placement (one tile forward diagonal)
bool Pawn::valid_capture_placement(Tile new_pos) const {
    const int row_diff = new_pos.row - get_row();
    const int col_abs_diff = abs(new_pos.col - get_col());

    // Valid if move 1 tile diagonally
    // White pawn must capture up one col. Black pawn capture down one col
    return col_abs_diff == 1 && (get_player() == Player::WHITE ? row_diff == 1 :
        row_diff == -1);
}