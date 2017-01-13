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
	~Tile() {}
	bool operator==(const Tile &other) const {
		return row == other.row && col == other.col;
	}
	bool operator!=(const Tile &other) const {
		return !(*this == other);
	}
	friend std::ostream &operator<<(std::ostream &os, const Tile &pos) {
		os << (char)(pos.col + 'a') << pos.row + 1;
		return os;
	}
	int row;
	int col;
};

#endif  // TILE_H
