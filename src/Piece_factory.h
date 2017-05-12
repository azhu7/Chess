/**
    Author: Alexander Zhu
    Date Created: March 31, 2017
    Description: Simple form of factory.
*/

#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include "Piece.h"

// Allocates and initializes piece based on supplied information. Throws error
// on invalid type.
Piece *create_piece(Player player, Tile pos, char type);

#endif  // !PIECE_FACTORY_H