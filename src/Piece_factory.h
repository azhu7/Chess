#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include "Piece.h"

Piece *create_piece(Player color, Tile pos, Piece::PieceType type);

#endif  // !PIECE_FACTORY_H