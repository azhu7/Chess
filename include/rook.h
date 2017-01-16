/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Rook piece
*/

#ifndef ROOK_H
#define ROOK_H

#include "linear_piece.h"

class Rook : public LinearPiece {
public:
    explicit Rook(const Player color = Player::WHITE, const Tile &pos = Tile())
        : LinearPiece{ color, pos }, has_moved_{ false } {}

    bool has_moved() const { return has_moved_; }

    // Can only set to true because can't "un-move"
    void set_moved() { has_moved_ = true; }

    // Inherited from Piece base class
    PieceType get_type() const override { return R; };

    // Inherited from Piece base class
    bool valid_placement(const Tile &new_pos) const override {
        const Tile cur_pos = get_pos();
        return (horizontal_path(cur_pos, new_pos) || vertical_path(cur_pos, new_pos)) &&
            cur_pos != new_pos;
    }

    // Inherited from LinearPiece class
    Direction get_direction(const Tile &new_pos) const override {
        // Move horizontally
        if (new_pos.row == get_row())
            return new_pos.col > get_col() ? E : W;
        // Move vertically
        return new_pos.row > get_row() ? N : S;
    }

private:
    bool has_moved_;
};

#endif  // ROOK_H