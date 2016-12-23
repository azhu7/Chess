#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
private:

public:
	Rook(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~Rook() {}

	// Inherited from Piece base class
	char get_type() const { return 'R'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // ROOK_H