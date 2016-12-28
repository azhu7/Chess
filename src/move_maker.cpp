#include "../include/move_maker.h"
#include "../include/pawn.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/rook.h"
#include "../include/queen.h"
#include "../include/king.h"

static const Tile P1_KING_START = Tile{ 0, 4 };
static const Tile P2_KING_START = Tile{ 7, 4 };

////////// BEGIN PUBLIC FUNCTIONS //////////

MoveMaker::MoveMaker(Board *board)
	: board_{ board }, p1_king{ P1_KING_START }, p2_king{ P2_KING_START },
	turn_ { Player::WHITE } {}

bool MoveMaker::make_move(const Tile &old_pos, const Tile& new_pos) {
	if (!valid_move(old_pos, new_pos)) {
		std::cout << ">>> Invalid move. Try again! <<<\n";
		return false;  // Unsuccessful move
	}

	Piece *cur_piece = (*board_)[old_pos];
	Piece *target_tile = (*board_)[new_pos];
	if (target_tile) {
		// Capture enemy piece
		assert(target_tile->get_player() != turn_);  // Make sure enemy piece
		delete target_tile;
		target_tile = nullptr;
	}
	cur_piece->set_pos(new_pos);  // Update piece coordinates
	if (cur_piece->get_type() == 'K') {
		King *temp_king = static_cast<King *>(cur_piece);
		temp_king->set_moved(true);  // King has moved (can no longer castle)
		update_king_pos(cur_piece);
	}
	board_->move(old_pos, new_pos);  // Move piece
	assert(!board_->get_tile(old_pos));  // Old tile should contain nullptr
	switch_turns();  // Switch turns upon successful move
	return true;
}

////////// BEGIN PRIVATE FUNCTIONS //////////

void MoveMaker::switch_turns() {
	turn_ = turn_ == Player::WHITE ? Player::BLACK : Player::WHITE;
}

bool MoveMaker::collision(const Tile &old_pos, const Tile &new_pos,
	const Direction &direction) const {
	Tile current_tile = old_pos;

	// Determine direction to move
	int vert_mvmt = -1;  // Down if South
	int horiz_mvmt = -1;  // Left if West
	if (direction == Direction::N || direction == Direction::NE || 
		direction == Direction::NW) {
		vert_mvmt = 1;  // Up if North
	}
	else if (direction == Direction::E || direction == Direction::W) {
		vert_mvmt = 0;  // None if neither North or South
	}
	if (direction == Direction::E || direction == Direction::NE || 
		direction == Direction::SE) {
		horiz_mvmt = 1;  // Right if East
	}
	else if (direction == Direction::N || direction == Direction::S) {
		horiz_mvmt = 0;  // None if neither West nor East
	}

	// Increment b/c don't check start tile
	current_tile.row += vert_mvmt;
	current_tile.col += horiz_mvmt;
	// Scan for collisions
	while (current_tile != new_pos) {
		if (board_->get_tile(current_tile)) {
			return true;
		}
		// Move in specified direction
		current_tile.row += vert_mvmt;
		current_tile.col += horiz_mvmt;
	}
	return false;
}

bool MoveMaker::valid_castle(const Tile & cur_pos) const
{
	std::cout << "Unimplemented\n";
	return false;
}

bool MoveMaker::valid_move(const Tile &old_pos, const Tile &new_pos) const {
	if (!(board_->tile_in_bounds(new_pos) && board_->tile_in_bounds(old_pos))) {
		std::cout << "Input tile is out of bounds\n";
		return false;
	}

	Piece *cur_piece = (*board_)[old_pos];
	Piece *new_tile = (*board_)[new_pos];
	if (!cur_piece) {
		return false;  // Player selected empty tile
	}

	// Players move their own pieces
	bool move_own_piece = cur_piece->get_player() == turn_;
	// Can't move onto own piece
	bool capture_own_piece = new_tile ? new_tile->get_player() == 
		cur_piece->get_player() : false;
	if (!move_own_piece) {
		std::cout << "Can't move enemy piece\n";
		return false;
	}
	else if (capture_own_piece) {
		std::cout << "Can't capture own piece\n";
		return false;
	}

	// Okay physical placement
	bool okay_placement = cur_piece->valid_placement(new_pos);
	// Check unique cases
	char piece_type = cur_piece->get_type();
	switch (piece_type) {
	case 'P': {
		// Pawn capture different than move
		const Piece *target_tile = board_->get_tile(new_pos);
		// If vertical move, make sure target spot is empty
		if (okay_placement) {
			okay_placement = !target_tile;
			if (abs(new_pos.row - old_pos.row) == 2) {
				// Check tile one above/below pawn
				Tile one_tile_away = Tile{ old_pos.row + (new_pos.row - old_pos.row) / 2, old_pos.col };
				okay_placement = okay_placement && !board_->get_tile(one_tile_away);  // Both tiles clear
			}
		}
		else {
			// Otherwise, check if pawn is capturing an enemy piece
			Pawn *temp_pawn = static_cast<Pawn *>(cur_piece);
			okay_placement = temp_pawn->valid_capture(new_pos) &&
				target_tile && target_tile->get_player() != turn_;
		}
		break;
	}
	case 'B': case 'R': case 'Q': {
		if (okay_placement) {
			// Check for any pieces between linear piece and target tile
			LinearPiece *temp_linear_piece = static_cast<LinearPiece *>(cur_piece);
			Direction move_direction = temp_linear_piece->get_direction(new_pos);
			okay_placement = !collision(old_pos, new_pos, move_direction);
		}
		break;
	}
	case 'K': {
		if (!okay_placement) {
			King *temp_king = static_cast<King *>(cur_piece);
			okay_placement = valid_castle(old_pos);
		}
		break;
	}
	case 'N': {
		// No special case for Knights
		break;
	}
	default: {
		break;
	}
	}
	// TODO: Checks on own piece = invalid; checks on enemy piece = update checked_
	return okay_placement;
}