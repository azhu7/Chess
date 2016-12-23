#include "piece.h"

Piece::Piece(const Piece & other)
{
	std::cout << "unimplemented\n";
}

Piece & Piece::operator=(const Piece & other)
{
	std::cout << "unimplemented\n";
	// TODO: insert return statement here
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Piece *p) {
	os << p->get_player() << p->get_type();
	return os;
}