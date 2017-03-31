/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Rook piece
*/

#ifndef ROOK_H
#define ROOK_H

#include "Linear_piece.h"

class Rook : public LinearPiece {
public:
    explicit Rook(Player color_, Tile pos_)
        : LinearPiece{ color_, pos_ }, moved{ false } {}

    bool has_moved() const { return moved; }

    // Can only set to true because can't "un-move"
    void set_moved() { moved = true; }

    // Inherited from Piece base class
    PieceType get_type() const override { return R; };

    // Inherited from Piece base class
    bool valid_placement(Tile new_pos) const override {
        const Tile cur_pos = get_pos();
        return (horizontal_path(cur_pos, new_pos) || vertical_path(cur_pos, new_pos)) &&
            cur_pos != new_pos;
    }

    // Inherited from LinearPiece class
    Direction get_direction(Tile new_pos) const override {
        // Move horizontally
        if (new_pos.row == get_row())
            return new_pos.col > get_col() ? E : W;
        // Move vertically
        return new_pos.row > get_row() ? N : S;
    }

private:
    bool moved;
};

#endif  // !ROOK_H