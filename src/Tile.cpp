/**
    Author: Alexander Zhu
    Date Created: December 22, 2016
    Description: Implementation for board tile
*/

#include "Tile.h"

#include <ostream>

using std::ostream;

ostream &operator<<(ostream &os, Tile pos) {
    return os << (char)(pos.col + 'a') << pos.row + 1;
}