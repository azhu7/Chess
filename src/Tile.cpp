/**
    Author: Alexander Zhu
    Date Created: December 22, 2016
    Description: Implementation for Board tile
*/

#include "Tile.h"

#include "Board.h"

#include <ostream>

using std::ostream;

// Convert 2D Tile to 1D array index
Tile::operator int() const {
    return row + Board::kNum_cols * col;
}

// Print Tile in the format [col][row]. Example: a2
ostream &operator<<(ostream &os, Tile pos) {
    return os << (char)(pos.col + 'a') << pos.row + 1;
}
