/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Bishop piece
*/

#ifndef BISHOP_H
#define BISHOP_H

#include "Linear_piece.h"

#include "Utility.h"

class Bishop : public LinearPiece {
public:
    explicit Bishop(Player color_, Tile pos_)
        : LinearPiece{ color_, pos_ } {}

    // Inherited from Piece base class
    PieceType get_type() const override { return B; };

protected:
    // Inherited from Piece base class
    bool valid_physical_placement(Tile new_pos) const override {
        return diagonal_path(get_pos(), new_pos) && get_pos() != new_pos;
    }

};

#endif  // !BISHOP_H