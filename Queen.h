#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
private:

public:
	Queen(const Player color_in, const unsigned col_in, const unsigned row_in)
		: Piece{ color_in, col_in, row_in } {}
	~Queen() {}

	char get_type() const;

	bool valid_placement(const unsigned new_col, const unsigned new_row) const;
};

inline char Queen::get_type() const {
	return 'Q';
}

bool Queen::valid_placement(const unsigned new_col, const unsigned new_row) const {
	return true;
}

#endif // QUEEN_H