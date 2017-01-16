/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for King piece
*/

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    explicit King(const Player color = Player::WHITE, const Tile &pos = Tile())
        : Piece{ color, pos }, has_moved_{ false } {}

    bool has_moved() const { return has_moved_; }

    // Can only set to true because can't "un-move"
    void set_moved() { has_moved_ = true; }

    // Inherited from Piece base class
    PieceType get_type() const override { return K; };

    // Inherited from Piece base class
    bool valid_placement(const Tile &new_pos) const override {
        const int row_abs_diff = abs(new_pos.row - get_row());
        const int col_abs_diff = abs(new_pos.col - get_col());
        return row_abs_diff == 1 || col_abs_diff == 1;
    }

private:
    bool has_moved_;  // Can only castle if !moved_
};

#endif  // KING_H