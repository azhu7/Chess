/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for abstract Piece
*/

#include "Piece.h"

// Determine if piece can move to new position. Utilizes Template Method
// and Non-virtual Interface patterns to customize behavior.
bool Piece::valid_move(Tile new_pos) const {
    bool okay_placement = valid_physical_placement(new_pos);
    return additional_placement_checks(okay_placement, new_pos);
}
