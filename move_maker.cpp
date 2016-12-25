#include "move_maker.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

static const Tile P1_KING_START = Tile{ 0, 4 };
static const Tile P2_KING_START = Tile{ 7, 4 };

MoveMaker::MoveMaker(Board & board)
	: board_{ board }, p1_king{ P1_KING_START }, p2_king{ P2_KING_START }, 
	turn_ { Player::WHITE } {}

bool MoveMaker::make_move(const Tile &old_pos, const Tile& new_pos) {
	if (!valid_move(old_pos, new_pos)) {
		std::cout << ">>> Invalid move. Try again! <<<\n";
		return false;  // Unsuccessful move
	}

	Piece *&cur_piece = board_.get_tile(old_pos);
	Piece *&target_tile = board_.get_tile(new_pos);
	if (target_tile) {
		// Capture enemy piece
		assert(target_tile->get_player() != turn_);  // Make sure enemy piece
		delete target_tile;
		target_tile = nullptr;
	}
	cur_piece->set_pos(new_pos);  // Update piece coordinates
	board_.move(old_pos, new_pos);  // Move piece
	assert(!board_.get_tile(old_pos));  // Old tile should contain nullptr
	switch_turns();  // Switch turns upon successful move
	return true;
}

void MoveMaker::switch_turns() {
	turn_ = turn_ == Player::WHITE ? Player::BLACK : Player::WHITE;
}

bool MoveMaker::valid_move(const Tile &old_pos, const Tile &new_pos) const {
	if (!(board_.tile_in_bounds(new_pos) && board_.tile_in_bounds(old_pos))) {
		std::cout << "Input tile is out of bounds\n";
		return false;
	}

	Piece *cur_piece = board_.get_tile(old_pos);
	Piece *new_tile = board_.get_tile(new_pos);

	if (!cur_piece) {
		return false;  // Player selected empty tile
	}

	// Players move their own pieces
	bool correct_team = cur_piece->get_player() == turn_;
	// Okay physical placement
	bool placement = cur_piece->valid_placement(new_pos);

	// Check unique cases
	char piece_type = cur_piece->get_type();
	switch (cur_piece->get_type()) {
	case 'P': {
		// Pawn capture different than move
		Piece *&target_tile = board_.get_tile(new_pos);
		// If vertical move, make sure target spot is empty
		if (placement) {
			placement = !target_tile;
			if (abs(new_pos.row - old_pos.row) == 2) {
				// Check tile one above/below pawn
				Tile one_tile_away = Tile{ old_pos.row + (new_pos.row - old_pos.row) / 2, old_pos.col };
				placement = placement && !board_.get_tile(one_tile_away);  // Both tiles clear
			}
		}
		else {
			// Otherwise, check if pawn is capturing an enemy piece
			Pawn *temp_pawn = static_cast<Pawn *>(cur_piece);
			placement = temp_pawn->valid_capture(new_pos) &&
				target_tile && target_tile->get_player() != turn_;
		}
		break;
	}
	case 'B': {
		//Bishop *temp_bishop = static_cast<Bishop *>(cur_piece);
		//Bishop::Direction move_direction = temp_bishop->get_direction(new_pos);
		//placement = !detect_collision(old_pos, new_pos, move_direction);
		break;
	}
	case 'R': {
		//placement = horizontal_collision(old_pos, new_pos);
		break;
	}
	case 'Q': {
		
		break;
	}
	}
	// Can't move onto own piece
	bool same_team = new_tile ? new_tile->get_player() == cur_piece->get_player() : false;

	return correct_team && placement && !same_team;
}