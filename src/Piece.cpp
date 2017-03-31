#include "Piece.h"

#include <ostream>

using std::ostream;
using std::underlying_type;

ostream &operator<<(ostream &os, const Piece::PieceType pt) {
    return os << static_cast<underlying_type<Piece::PieceType>::type>(pt);
}

ostream &operator<<(ostream &os, const Piece *p) {
    return os << p->get_player() << p->get_type();
}