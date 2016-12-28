/*
*  Author: Alexander Zhu
*  Date Created: December 22, 2016
*  Description: Header file for board tile
*/

#ifndef TILE_H
#define TILE_H

struct Tile {
	explicit Tile(const int row = -1, const int col = -1)
		: row{ row }, col{ col } {}
	Tile(const Tile &other) {
		row = other.row;
		col = other.col;
	}
	Tile &operator=(const Tile &other) {
		if (this == &other) {
			return *this;
		}
		row = other.row;
		col = other.col;
		return *this;
	}
	~Tile() {}

	bool operator!=(const Tile &other) const {
		return row != other.row || col != other.col;
	}
	int row;
	int col;
};

#endif  // TILE_H
