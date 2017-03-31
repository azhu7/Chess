#include "../include/queen.h"

LinearPiece::Direction Queen::get_direction(const Tile &new_pos) const {
    const Tile cur_pos = get_pos();
    // Move upwards (N)
    if (new_pos.row > cur_pos.row) {
        if (new_pos.col > cur_pos.col)
            return NE;
        return new_pos.col < cur_pos.col ? NW : N;
    }
    // Move horizontally
    if (new_pos.row == cur_pos.row)
        return new_pos.col < cur_pos.col ? W : E;
    // Move downwards (S)
    if (new_pos.col > cur_pos.col)
        return SE;
    return new_pos.col < cur_pos.col ? SW : S;
}
