#include "../include/piece.h"

std::ostream &operator<<(std::ostream &os, const Piece::PieceType pt) {
    return os << static_cast<std::underlying_type<Piece::PieceType>::type>(pt);
}

std::ostream &operator<<(std::ostream &os, const Piece *p) {
    return os << p->get_player() << p->get_type();
}