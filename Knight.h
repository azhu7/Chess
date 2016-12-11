#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
private:

public:
	Knight(const Player color_in, const int col_in, const int row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Knight() {}

	// Inherited from Piece base class
	char get_type() const { return 'N'; }

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // KNIGHT_H