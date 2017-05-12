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
    char get_type() const override { return 'N'; }

private:
    // Inherited from Piece base class
    // Return true if L-shaped path from old pos to new pos
    bool valid_physical_placement(Tile new_pos) const override;
};

#endif  // !KNIGHT_H