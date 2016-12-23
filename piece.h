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
private:
	Player color_;
	int row_;
	int col_;

public:
	Piece() {}
	Piece(const Player color_in, const Tile &pos)
		: color_{ color_in }, col_{ pos.col }, row_{ pos.row } {}
	Piece(const Piece &other);
	Piece &operator=(const Piece &other);

	~Piece() {}

	Player get_player() const {
		return color_;
	}

	int get_row() const {
		return row_;
	}

	int get_col() const {
		return col_;
	}

	Tile get_pos() const {
		return Tile{ row_, col_ };
	}

	void set_coords(const Tile &pos) {
		col_ = pos.col;
		row_ = pos.row;
	}

	// EFFECTS  Return piece type as char ('P' = Pawn, 'R' = Rook, etc.)
	virtual char get_type() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Piece *p);

	// REQUIRES pos is a valid coordinate
	// EFFECTS  Determine if piece is physically allowed to move to new position.
	//          Does not take into account other pieces at that position.
	virtual bool valid_placement(const Tile &pos) const = 0;
};

#endif  //PIECE_H
