#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
private:

public:
	Rook(const Player color_in, const int col_in, const int row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Rook() {}

	// Inherited from Piece base class
	char get_type() const { return 'R'; }

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // ROOK_H