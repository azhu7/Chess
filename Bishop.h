#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:

public:
	Bishop(const Player color_in, const int col_in, const int row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Bishop() {}

	// Inherited from Piece base class
	char get_type() const { return 'B'; };

	// Inherited from Piece base class
	bool valid_placement(const int new_col, const int new_row) const;
};

#endif // BISHOP_H