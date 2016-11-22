#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:

public:
	Bishop(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Bishop() {}

	char get_type() const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char Bishop::get_type() const {
	return 'B';
}

bool Bishop::valid_placement(const unsigned new_col, const unsigned new_row) const {
	return true;
}

#endif // BISHOP_H