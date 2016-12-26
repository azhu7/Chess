/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for abstract piece
*/

#ifndef PIECE_H
#define PIECE_H

#include "player.h"
#include "tile.h"
#include <iostream>
#include <cassert>

class Piece {
public:
	explicit Piece(const Player color = Player::WHITE, const Tile &pos = Tile())
		: color_{ color }, row_{ pos.row }, col_{ pos.col } {}
	Piece(const Piece &other);  // TODO  Remove copy ctor and assignment operator b/c don't need?
	Piece &operator=(const Piece &other);

	virtual ~Piece() {}

	const Player &get_player() const { return color_; }

	int get_row() const { return row_; }

	int get_col() const { return col_; }

	const Tile get_pos() const { return Tile{ row_, col_ }; }

	void set_pos(const Tile &pos) {
		row_ = pos.row;
		col_ = pos.col;
	}

	// EFFECTS  Return piece type as char ('P' = Pawn, 'R' = Rook, etc.)
	virtual char get_type() const = 0;

	// REQUIRES pos is a valid coordinate
	// EFFECTS  Determine if piece is physically allowed to move to new position.
	//          Does not take into account other pieces at that position.
	virtual bool valid_placement(const Tile &new_pos) const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Piece *p) {
		os << p->get_player() << p->get_type();
		return os;
	}

private:
	Player color_;
	int row_;
	int col_;
};

#endif  //PIECE_H
