/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Queen piece
*/

#ifndef QUEEN_H
#define QUEEN_H

#include "Linear_piece.h"

class Queen : public LinearPiece {
public:
    explicit Queen(const std::string &id_, Player player_, Tile pos_)
        : LinearPiece{ id_, player_, pos_ } {}

    // Inherited from Piece base class
    char get_type() const override { return 'Q'; }

protected:
    // Inherited from Piece base class
    bool valid_physical_placement(Tile new_pos) const override {
        const Tile cur_pos = get_pos();
        return (diagonal_path(cur_pos, new_pos) ||
            horizontal_path(cur_pos, new_pos) ||
            vertical_path(cur_pos, new_pos)) && cur_pos != new_pos;
    }
};

#endif  // !QUEEN_H