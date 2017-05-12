/**
    Author: Alexander Zhu
    Date Created: May 11, 2017
    Description: Implementation for King piece
*/

#include "King.h"

#include "Board.h"
#include "Rook.h"
#include "Utility.h"

#include <cassert>
#include <cmath>

const Tile King::P1_KING_START{ 0, 4 };
const Tile King::P2_KING_START{ 7, 4 };

bool King::valid_physical_placement(Tile new_pos) const {
    const int row_abs_diff = abs(new_pos.row - get_row());
    const int col_abs_diff = abs(new_pos.col - get_col());
    return row_abs_diff == 1 || col_abs_diff == 1;
}

bool King::valid_castle(Tile new_pos) const {
    if (moved)
        return false;  // Can't castle if already moved

    const Tile cur_pos = get_pos();
    assert(cur_pos.col == P1_KING_START.col);  // king should be in starting position

    // Lambda to check that rook hasn't moved and no collisions from king to rook
    static auto rook_and_collision_check = [&](Tile cur_pos, int rook_col,
        const Direction direction) {
        // Check corner for rook
        const Tile rook_tile{ cur_pos.row, rook_col };
        if (Rook *rook = dynamic_cast<Rook *>(Board::get_instance().get_tile(rook_tile))) {
            // Check that rook has not moved and no horizontal collision to the right
            return !(rook->has_moved() || collision(cur_pos, rook_tile, direction));
        }
        return false;
    };

    // Castle right: check right of king
    if (new_pos == Tile{ cur_pos.row, Board::kKingRightCastledCol })
        return rook_and_collision_check(cur_pos, Board::kRightRookInitCol, Direction::E);
    // Castle left: check left of king
    else if (new_pos == Tile{ cur_pos.row, Board::kKingLeftCastledCol })
        return rook_and_collision_check(cur_pos, Board::kLeftRookInitCol, Direction::W);
    // new_pos is not a valid castle tile
    return false;
}