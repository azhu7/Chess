#ifndef MOVE_MAKER_H
#define MOVE_MAKER_H

#include "board.h"
#include "player.h"

// Wrapper class for Board object
class MoveMaker {
public:
	explicit MoveMaker::MoveMaker(Board &board = Board())
		: board_{ board }, turn_{ Player::WHITE } {}
	~MoveMaker() {};

	// EFFECTS  Return current player
	const Player &get_current_player() const { return turn_; }

	// MODIFIES board_
	// EFFECTS  Move piece to new tile
	// TODO		Update to return different enum codes
	bool make_move(const Tile &old_pos, const Tile &new_pos);

private:
	Board &board_;
	Player turn_;
	Player checked_;  // Player whose King is under attack

	// MODIFIES turn_
	// EFFECTS  Updates whose turn it is
	void switch_turns();

	// REQUIRES horizontal path from old_pos to new_pos
	// EFFECTS  Check for any pieces between old_pos and new_pos (non-inclusive)
	bool horizontal_collision(const Tile &old_pos, const Tile &new_pos) const;

	// REQUIRES vertical path from old_pos to new_pos
	// EFFECTS  Check for any pieces between old_pos and new_pos (non-inclusive)
	bool vertical_collision(const Tile &old_pos, const Tile &new_pos) const;

	// REQUIRES diagonal path from old_pos to new_pos
	// EFFECTS  Check for any pieces between old_pos and new_pos (non-inclusive)
	bool diagonal_collision(const Tile &old_pos, const Tile &new_pos) const;

	// EFFECTS  Determine if piece can be moved to new tile.
	//			Make sure piece moves according to Chess rules.
	bool valid_move(const Tile &old_pos, const Tile &new_pos) const;

	// EFFECTS  Upon a successful move, detect any checks
	bool detect_check() const;

	// EFFECTS  Upon a check, detect checkmate
	bool detect_checkmate() const;
};

#endif  // MOVE_MAKER_H
