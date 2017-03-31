/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Knight piece
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    explicit Knight(Player color_, Tile pos_)
        : Piece{ color_, pos_ } {}

    // Inherited from Piece base class
    PieceType get_type() const override { return N; };

    // Inherited from Piece base class
    bool valid_placement(Tile new_pos) const override {
        return l_shape_move(new_pos);
    }

private:
    // EFFECTS  Return true if l-shaped path from old pos to new pos
    //          Used by Knight
    bool l_shape_move(Tile new_pos) const {
        const int row_abs_diff = abs(new_pos.row - get_row());
        const int col_abs_diff = abs(new_pos.col - get_col());
        return (row_abs_diff == 1 && col_abs_diff == 2) || 
            (row_abs_diff == 2 && col_abs_diff == 1);
    }
};

#endif  // !KNIGHT_H