/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for abstract piece
*/

// TODO: CHECK RULES FOR EN PASSANT (NEED TO CAPTURE IMMEDIATELY? IF SO, TRACK IN MOVE_MAKER INSTEAD)

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

// Starting rows
const int kWhitePawnStart = 1;
const int kBlackPawnStart = 6;

class Pawn : public Piece {
public:
	explicit Pawn(const Player color = Player::WHITE, const Tile &pos = Tile())
		: Piece{ color, pos }, two_tile_move{ false } {}
	~Pawn() {}

	// Inherited from Piece base class
	PieceType get_type() const override { return PieceType::P; }

	bool last_move_two_tiled() { return two_tile_move; }  // TODO: Rename

	void set_two_tile_move(bool two_tile_move) { two_tile_move = two_tile_move; }  // TODO: Rename

	// REQUIRES new_pos or en_passant_pos contains enemy piece
	// EFFECTS  Determine if capture is valid
	bool valid_capture(const Tile &new_pos, const Tile &en_passant_pos) const;

	// Inherited from Piece base class
	bool valid_placement(const Tile &new_pos) const override;

private:
	bool two_tile_move;  // True if previous move was two tiles  // TODO: Rename
};

#endif  // PAWN_H