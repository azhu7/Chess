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
	Piece(const Piece &other) = delete; 
	Piece(Piece &&other) = delete;
	const Piece &operator=(const Piece &other) = delete;
	Piece &operator=(Piece &&other) = delete;

	virtual ~Piece() {}

	// Getters
	const Player &get_player() const { return color_; }
	int get_row() const { return row_; }
	int get_col() const { return col_; }

	// EFFECTS  Returns piece position as Tile. Useful for passing into functions.
	const Tile get_pos() const { return Tile{ row_, col_ }; }

	void set_pos(const Tile &pos) {
		row_ = pos.row;
		col_ = pos.col;
	}

	enum class PieceType : char {
		P = 'P', B = 'B', N = 'N', R = 'R', Q = 'Q', K = 'K'
	};

	friend std::ostream &operator<<(std::ostream &os, const PieceType pt) {
		return os << static_cast<std::underlying_type<PieceType>::type>(pt);
	}

	// EFFECTS  Return piece type
	virtual PieceType get_type() const = 0;

	// REQUIRES pos is a valid coordinate
	// EFFECTS  Determine if piece is physically allowed to move to new position.
	//          Does not take into account other pieces at that position or along
	//			the way.
	virtual bool valid_placement(const Tile &new_pos) const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Piece *p) {
		return os << p->get_player() << p->get_type();
	}

private:
	Player color_;
	int row_;
	int col_;
};

#endif  //PIECE_H
