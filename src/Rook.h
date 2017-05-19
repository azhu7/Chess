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
    explicit Rook(const std::string &id_, Player player_, Tile pos_)
        : LinearPiece{ id_, player_, pos_ } {}

    bool has_moved() const { return moved; }

    // Can only set to true because can't "un-move"
    void set_moved() override { moved = true; }

    // Inherited from Piece base class
    char get_type() const override { return 'R'; }

protected:
    // Inherited from Piece base class
    bool valid_physical_placement(Tile new_pos) const override {
        const Tile cur_pos = get_pos();
        return (horizontal_path(cur_pos, new_pos) || vertical_path(cur_pos, new_pos)) &&
            cur_pos != new_pos;
    }

private:
    bool moved = false;
};

#endif  // !ROOK_H