#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
private:

public:
	King(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~King() {}

	// Inherited from Piece base class
	char get_type() const { return 'K'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // KING_H