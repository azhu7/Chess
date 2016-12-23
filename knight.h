#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
private:

public:
	Knight(const Player color_in, const Tile &pos)
		: Piece{ color_in, pos } {}
	~Knight() {}

	// Inherited from Piece base class
	char get_type() const { return 'N'; }

	// EFFECTS  Return true if l-shaped path from old pos to new pos
	//			Used by Knight
	bool l_shape_move(const Tile &old_pos, const Tile &new_pos);

	// Inherited from Piece base class
	bool valid_placement(const Tile &pos) const;
};

#endif // KNIGHT_H