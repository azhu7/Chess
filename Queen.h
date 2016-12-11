#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
private:

public:
	Queen(const Player color_in, const int col_in, const int row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Queen() {}

	// Inherited from Piece base class
	char get_type() const { return 'Q'; }

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // QUEEN_H