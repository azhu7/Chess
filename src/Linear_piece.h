/**
    Author: Alexander Zhu
    Date Created: December 23, 2016
    Description: A linear piece can move in an extended straight line (more than 
                 one tile)
*/

#ifndef LINEAR_PIECE_H
#define LINEAR_PIECE_H

#include "Piece.h"

#include <algorithm>

enum class Direction : int;

class LinearPiece : public Piece {
public:
    explicit LinearPiece(const std::string &id_, Player player_, Tile pos_)
        : Piece{ id_, player_, pos_ } {}

    // REQUIRES Straight path from current pos to new_pos
    // Determine relative direction to new_pos.
    //          Used to aid MoveMaker detect collision functions.
    Direction get_direction(Tile new_pos) const;

protected:
    // Inherited from Piece base class
    bool additional_placement_checks(bool valid_physical_placement,
        Tile new_pos) const override;

    // Return true if horizontal path from old pos to new pos
    //          Used by Rook and Queen
    bool horizontal_path(Tile old_pos, Tile new_pos) const {
        return old_pos.row == new_pos.row;
    }

    // Return true is vertical path from old pos to new pos
    //          Used by Rook and Queen
    bool vertical_path(Tile old_pos, Tile new_pos) const {
        return old_pos.col == new_pos.col;
    }

    // Return true if diagonal path from old pos to new pos
    //          Used by Bishop and Queen
    bool diagonal_path(Tile old_pos, Tile new_pos) const {
        // Find top_right and bottom_left corners of box created by old_pos and new_pos
        Tile top_right{ std::max(old_pos.row, new_pos.row),
            std::max(old_pos.col, new_pos.col) };
        Tile bottom_left{ std::min(old_pos.row, new_pos.row),
            std::min(old_pos.col, new_pos.col) };
        return top_right.row - bottom_left.row == top_right.col - bottom_left.col;
    }
};

#endif  // !LINEAR_PIECE_H
