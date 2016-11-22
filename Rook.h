#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
private:

public:
	Rook(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Rook() {}

	char get_type() const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char Rook::get_type() const {
	return 'R';
}

bool Rook::valid_placement(const unsigned new_col, const unsigned new_row) const {
	return true;
}

#endif // ROOK_H