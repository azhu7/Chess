#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
private:

public:
	Queen(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~Queen() {}

	// Inherited from Piece base class
	char get_type() const { return 'Q'; }

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // QUEEN_H