#ifndef TILE_H
#define TILE_H

struct Tile {
	Tile(const int row_in, const int col_in)
		: row{ row_in }, col{ col_in } {}
	Tile()
		: row{ -1 }, col{ -1 } {}
	int row;
	int col;
};

#endif // !TILE_H
