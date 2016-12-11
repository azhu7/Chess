#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
private:

public:
	King(const Player color_in, const int col_in, const int row_in)
		: Piece{ color_in, col_in, row_in } {}
	~King() {}

	// Inherited from Piece base class
	char get_type() const { return 'K'; }

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // KING_H