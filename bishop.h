#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
private:

public:
	Bishop(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~Bishop() {}

	// Inherited from Piece base class
	char get_type() const { return 'B'; };

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // BISHOP_H