/**
    Author: Alexander Zhu
    Date Created: March 31, 2017
    Description: Simple form of factory.
*/

#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

class Piece;
struct Tile;
enum Player : int;

#include <memory>

// Allocates and initializes piece based on supplied information. Throws error
// on invalid type.
std::shared_ptr<Piece> create_piece(Player player, Tile pos, char type);

#endif  // !PIECE_FACTORY_H