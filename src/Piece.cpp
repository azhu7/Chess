/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for abstract piece
*/

#include "Piece.h"

#include <ostream>

using std::ostream;
using std::underlying_type;

ostream &operator<<(ostream &os, Piece::PieceType pt) {
    return os << static_cast<underlying_type<Piece::PieceType>::type>(pt);
}
ostream &operator<<(ostream &os, const Piece &p) {
    return os << p.get_player() << p.get_type();
}

// Determine if piece can move to new position. Utilizes Template Method
// and Non-virtual Interface patterns to customize behavior.
bool Piece::valid_move(Tile new_pos) const {
    bool okay_placement = valid_physical_placement(new_pos);
    return additional_placement_checks(okay_placement, new_pos);
}
