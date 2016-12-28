#include "../include/move_maker.h"
#include "../include/pawn.h"
#include "../include/bishop.h"
#include "../include/knight.h"
#include "../include/rook.h"
#include "../include/queen.h"

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
	const Piece *target_tile = board_->get_tile(new_pos);
	if (target_tile) {
		// Capture enemy piece
		assert(target_tile->get_player() != turn_);  // Make sure enemy piece
		delete target_tile;
		target_tile = nullptr;
	}
	// Rook special case
	if (cur_piece->get_type() == 'R') {
		Rook *temp_rook = static_cast<Rook *>(cur_piece);
		temp_rook->set_moved();  // Rook has moved (can no longer castle on this side)
	}
	// King special case
	else if (cur_piece->get_type() == 'K') {
		King *temp_king = static_cast<King *>(cur_piece);
		if (valid_castle(temp_king, new_pos)) {
			// On castle, update rook as well
			castle_update_rook(old_pos, new_pos);
		}
		temp_king->set_moved();  // King has moved (can no longer castle)
		set_king_pos(temp_king);
	}
	cur_piece->set_pos(new_pos);  // Update piece coordinates
	board_->move(old_pos, new_pos);  // Move piece
	assert(!board_->get_tile(old_pos));  // Old tile should contain nullptr
	switch_turns();  // Switch turns upon successful move
	return true;
}

////////// BEGIN PRIVATE FUNCTIONS //////////

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

void MoveMaker::castle_update_rook(const Tile &old_pos, const Tile &new_pos) {
	// lambda to move rook to castled position
	static auto move_rook_to_castled = [&](const int rook_col, 
		const int castled_col) {
		const Tile rook_pos{ old_pos.row, rook_col };
		const Tile castled_pos{ old_pos.row, castled_col };
		Rook *temp_rook = static_cast<Rook *>((*board_)[rook_pos]);
		board_->move(rook_pos, castled_pos);
		temp_rook->set_moved();
	};
	if (new_pos.col > old_pos.col) {
		// Castle to the right. Adjust right rook.
		move_rook_to_castled(Board::kRightRookInitCol, Board::kRightRookCastledCol);
	}
	else {
		// Castle to the left. Adjust left rook.
		move_rook_to_castled(Board::kLeftRookInitCol, Board::kLeftRookCastledCol);
	}
}

bool MoveMaker::valid_castle(const King *king, const Tile &new_pos) const {
	if (king->has_moved()) {
		return false;  // Can't castle if already moved
	}
	const Tile cur_pos = king->get_pos();
	assert(cur_pos.col == P1_KING_START.col);  // king should be in starting position

	// lambda to check that rook hasn't moved and no collisions from king to rook
	static auto rook_and_collision_check = [&](const Tile &cur_pos, const int rook_col, 
		const Direction direction) {
		// Check corner for rook
		const Tile rook_tile = Tile{ cur_pos.row, rook_col };
		const Piece *temp_piece = (*board_)[rook_tile];
		if (temp_piece->get_type() == 'R') {
			const Rook *temp_rook = static_cast<const Rook *>(temp_piece);
			// Check that rook has not moved and no horizontal collision to the right
			return !(temp_rook->has_moved() || collision(cur_pos, rook_tile, direction));
		}
		return false;
	};

	// Castle right: check right of king
	if (new_pos == Tile{ cur_pos.row, Board::kKingRightCastledCol }) {
		return rook_and_collision_check(cur_pos, Board::kRightRookInitCol, Direction::E);
	}
	// Castle left: check left of king
	else if (new_pos == Tile{ cur_pos.row, Board::kKingLeftCastledCol }) {
		return rook_and_collision_check(cur_pos, Board::kLeftRookInitCol, Direction::W);
	}
	// new_pos is not a valid castle tile
	return false;
}

bool MoveMaker::valid_move(const Tile &old_pos, const Tile &new_pos) const {
	if (!(board_->tile_in_bounds(new_pos) && board_->tile_in_bounds(old_pos))) {
		std::cout << "Input tile is out of bounds\n";
		return false;
	}

	const Piece *cur_piece = board_->get_tile(old_pos);
	const Piece *new_tile = board_->get_tile(new_pos);
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
		if (okay_placement) {
			okay_placement = !target_tile;  // If vertical move, make sure target spot is empty
			if (abs(new_pos.row - old_pos.row) == 2) {
				// Check tile one above/below pawn
				Tile one_tile_away = Tile{ (old_pos.row + new_pos.row) / 2, old_pos.col };
				// Both tiles clear
				okay_placement = okay_placement && !board_->get_tile(one_tile_away);
			}
		}
		else {
			// Otherwise, check if pawn is capturing an enemy piece
			const Pawn *temp_pawn = static_cast<const Pawn *>(cur_piece);
			okay_placement = temp_pawn->valid_capture(new_pos) &&
				target_tile && target_tile->get_player() != turn_;
		}
		break;
	}
	case 'B': case 'R': case 'Q': {
		if (okay_placement) {
			// Check for any pieces between linear piece and target tile
			const LinearPiece *temp_linear_piece = static_cast<const LinearPiece *>(cur_piece);
			Direction move_direction = temp_linear_piece->get_direction(new_pos);
			okay_placement = !collision(old_pos, new_pos, move_direction);
		}
		break;
	}
	case 'K': {
		if (!okay_placement) {
			const King *temp_king = static_cast<const King *>(cur_piece);
			okay_placement = valid_castle(temp_king, new_pos);
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