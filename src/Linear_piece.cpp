/**
    Author: Alexander Zhu
    Date Created: May 11, 2017
    Description: Implementation for abstract Linear_piece
*/

#include "Linear_piece.h"

#include "Utility.h"

/*
Public members
*/

Direction LinearPiece::get_direction(Tile new_pos) const {
    const Tile cur_pos = get_pos();
    // Move upwards (N)
    if (new_pos.row > cur_pos.row) {
        if (new_pos.col > cur_pos.col)
            return Direction::NE;
        return new_pos.col < cur_pos.col ? Direction::NW : Direction::N;
    }
    // Move horizontally
    if (new_pos.row == cur_pos.row)
        return new_pos.col < cur_pos.col ? Direction::W : Direction::E;
    // Move downwards (S)
    if (new_pos.col > cur_pos.col)
        return Direction::SE;
    return new_pos.col < cur_pos.col ? Direction::SW : Direction::S;
}

/*
Private members
*/

bool LinearPiece::additional_placement_checks(bool valid_physical_placement,
    Tile new_pos) const {
    if (valid_physical_placement) {
        // Check for any pieces between linear piece and target tile
        Direction move_direction = get_direction(new_pos);
        return !collision(get_pos(), new_pos, move_direction);
    }
    return valid_physical_placement;
}