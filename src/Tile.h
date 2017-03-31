/**
    Author: Alexander Zhu
    Date Created: December 22, 2016
    Description: Header file for board tile
*/

#ifndef TILE_H
#define TILE_H

#include <iosfwd>

struct Tile {
    explicit Tile(int row = -1, int col = -1)
        : row{ row }, col{ col } {}
    ~Tile() {}
    bool operator==(const Tile &rhs) const {
        return row == rhs.row && col == rhs.col;
    }
    bool operator!=(const Tile &rhs) const {
        return !(*this == rhs);
    }
    
    int row;
    int col;
};

std::ostream &operator<<(std::ostream &os, const Tile &pos);

#endif  // !TILE_H
