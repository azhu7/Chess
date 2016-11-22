#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
private:

public:
	Knight(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Knight() {}

	char get_type() const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char Knight::get_type() const {
	return 'N';
}

bool Knight::valid_placement(const unsigned new_col, const unsigned new_row) const {
	return true;
}

#endif // KNIGHT_H