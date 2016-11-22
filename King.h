#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
private:

public:
	King(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~King() {}

	char get_type() const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char King::get_type() const {
	return 'K';
}

bool King::valid_placement(const unsigned new_col, const unsigned new_row) const {
	return true;
}

#endif // KING_H