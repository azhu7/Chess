/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for King piece
*/

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    static const Tile P1_KING_START;
    static const Tile P2_KING_START;

    explicit King(Player color_, Tile pos_)
        : Piece{ color_, pos_ } {}

    bool has_moved() const { return moved; }

    // Can only set to true because can't "un-move"
    void set_moved() { moved = true; }

    // Inherited from Piece base class
    char get_type() const override { return 'K'; }

protected:
    // Inherited from Piece base class
    bool valid_physical_placement(Tile new_pos) const override;

    // Inherited from Piece base class
    bool additional_placement_checks(bool okay_placement, Tile new_pos) const 
        override;

private:
    bool moved = false;  // Can only castle if !moved

    // Check if this King can castle to new_pos
    bool valid_castle(Tile new_pos) const;
};

#endif  // !KING_H