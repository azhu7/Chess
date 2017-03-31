/**
    Author: Alexander Zhu
    Date Created: December 22, 2016
    Description: Header file for board tile
*/

#ifndef TILE_H
#define TILE_H

#include <iosfwd>

struct Tile {
    explicit Tile(int row_ = -1, int col_ = -1)
        : row{ row_ }, col{ col_ } {}
    ~Tile() {}

    bool operator==(Tile rhs) const {
        return row == rhs.row && col == rhs.col;
    }
    bool operator!=(Tile rhs) const {
        return !(*this == rhs);
    }
    
    friend std::ostream &operator<<(std::ostream &os, Tile pos);

    int row;
    int col;
};

#endif  // !TILE_H
