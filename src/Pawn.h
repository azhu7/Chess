/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for Pawn piece
*/

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

// Starting rows
const int kWhitePawnStart = 1;
const int kBlackPawnStart = 6;

class Pawn : public Piece {
public:
    explicit Pawn(Player color_, Tile pos_)
        : Piece{ color_, pos_ } {}

    // Inherited from Piece base class
    char get_type() const override { return 'P'; }

protected:
    // Inherited from Piece base class
    bool valid_physical_placement(Tile new_pos) const override;
    bool additional_placement_checks(bool valid_physical_placement,
        Tile new_pos) const override;

    // Determine if move is valid capture placement (one tile forward diagonal)
    bool valid_capture_placement(Tile new_pos) const;
};

#endif  // !PAWN_H