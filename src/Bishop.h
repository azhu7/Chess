/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Bishop piece
*/

#ifndef BISHOP_H
#define BISHOP_H

#include "Linear_piece.h"

class Bishop : public LinearPiece {
public:
    explicit Bishop(Player color_, Tile pos_)
        : LinearPiece{ color_, pos_ } {}

    // Inherited from Piece base class
    PieceType get_type() const override { return B; };

    // Inherited from Piece base class
    bool valid_placement(Tile new_pos) const override {
        return diagonal_path(get_pos(), new_pos) && get_pos() != new_pos;
    }

    // Inherited from LinearPiece class
    Direction get_direction(Tile new_pos) const override {
        // Move upwards (N)
        if (new_pos.row > get_row())
            return new_pos.col > get_col() ? NE : NW;
        // Move downwards (S)
        return new_pos.col > get_col() ? SE : SW;
    }
};

#endif  // !BISHOP_H