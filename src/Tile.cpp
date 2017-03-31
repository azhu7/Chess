#include "Tile.h"

#include <ostream>

using std::ostream;

ostream &operator<<(ostream &os, const Tile &pos) {
    return os << (char)(pos.col + 'a') << pos.row + 1;
}