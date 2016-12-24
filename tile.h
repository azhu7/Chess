#ifndef TILE_H
#define TILE_H

struct Tile {
	explicit Tile(const int row = -1, const int col = -1)
		: row{ row }, col{ col } {}
	int row;
	int col;
};

#endif // TILE_H
