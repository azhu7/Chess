/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for King piece
*/

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    explicit King(Player color_, Tile pos_)
        : Piece{ color_, pos_ }, moved{ false } {}

    bool has_moved() const { return moved; }

    // Can only set to true because can't "un-move"
    void set_moved() { moved = true; }

    // Inherited from Piece base class
    PieceType get_type() const override { return K; };

    // Inherited from Piece base class
    bool valid_placement(Tile new_pos) const override {
        const int row_abs_diff = abs(new_pos.row - get_row());
        const int col_abs_diff = abs(new_pos.col - get_col());
        return row_abs_diff == 1 || col_abs_diff == 1;
    }

private:
    bool moved;  // Can only castle if !moved
};

#endif  // !KING_H