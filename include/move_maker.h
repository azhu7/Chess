/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for MoveMaker, a wrapper class for the Board.
*				Used to enforce chess rules when moving pieces.
*/

#ifndef MOVE_MAKER_H
#define MOVE_MAKER_H

#include "board.h"
#include "player.h"
#include "linear_piece.h"

class MoveMaker {
public:
	explicit MoveMaker::MoveMaker(Board &board = Board());
	~MoveMaker() {};

	// EFFECTS  Return current player
	const Player &get_current_player() const { return turn_; }

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	// TODO		Update to return different enum codes
	bool make_move(const Tile &old_pos, const Tile &new_pos);

private:
	typedef LinearPiece::Direction Direction;  // TODO: Questionable Style?
	Board &board_;
	Tile p1_king;  // Track each player's king to help with check detection
	Tile p2_king;
	Player turn_;
	Player checked_;  // Player whose King is under attack

	// MODIFIES turn_
	// EFFECTS  Updates whose turn it is
	void switch_turns();

	// REQUIRES Straight path from current pos to new_pos
	// EFFECTS  Check for any pieces between old_pos and new_pos
	bool collision(const Tile &old_pos, const Tile &new_pos, 
		const Direction &direction) const;

	// EFFECTS  Determine if piece can be moved to new tile.
	//			Make sure piece moves according to Chess rules.
	bool valid_move(const Tile &old_pos, const Tile &new_pos) const;

	// EFFECTS  Upon a successful move, detect any checks
	// TODO		Accomplish by checking around King?
	bool detect_check() const;

	// EFFECTS  Upon a check, detect checkmate
	bool detect_checkmate() const;
};

#endif  // MOVE_MAKER_H
