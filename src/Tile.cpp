#include "../include/tile.h"

std::ostream &operator<<(std::ostream &os, const Tile &pos) {
    return os << (char)(pos.col + 'a') << pos.row + 1;
}