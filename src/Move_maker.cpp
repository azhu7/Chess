/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for MoveMaker
*/

#include "Move_maker.h"

#include "Bishop.h"
#include "Board.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include <iostream>

using std::cerr; using std::ostream;

static const Tile P1_KING_START{ 0, 4 };
static const Tile P2_KING_START{ 7, 4 };

/*
Move_maker public members
*/

Move_maker::Move_maker(Board *board_ptr)
    : board_{ board_ptr }, p1_king_{ P1_KING_START }, p2_king_{ P2_KING_START },
    last_en_passant_pos_{ Tile{} }, turn_{ Player::WHITE }, en_passant_{ false } {}

bool Move_maker::make_move(const Tile &old_pos, const Tile& new_pos) {
    if (!valid_move(old_pos, new_pos)) {
        cerr << ">>> Invalid move. Try again! <<<\n";
        return false;
    }

    Piece *cur_piece = board_->get_tile(old_pos);
    if (Piece *&target_tile = board_->get_tile(new_pos)) {
        // Capture enemy piece
        assert(target_tile->get_player() != turn_);  // Make sure enemy piece
        delete target_tile;
        target_tile = nullptr;
    }

    // Account for en passant capture
    if (en_passant_)
        capture_en_passant_pawn();
    last_en_passant_pos_ = Tile{};  // Reset en passant tile

    switch (cur_piece->get_type()) {
    case Piece::P: {
        // Check if pawn is moving two tiles. Needed for possible en passant.
        bool two_rank_move = abs(new_pos.row - old_pos.row) == 2 && new_pos.col == old_pos.col;
        if (two_rank_move)
            last_en_passant_pos_ = new_pos;
        break;
    }
    case Piece::R: {
        Rook *temp_rook = static_cast<Rook *>(cur_piece);
        temp_rook->set_moved();  // Rook has moved (can no longer castle on this side)
        break;
    }
    case Piece::K: {
        King *temp_king = static_cast<King *>(cur_piece);
        if (valid_castle(temp_king, new_pos))
            castle_update_rook(old_pos, new_pos);  // On castle, update rook as well
        temp_king->set_moved();  // King has moved (can no longer castle)
        set_king_pos(temp_king);
        break;
    }
    case Piece::B: case Piece::N: case Piece::Q:
        // No special case for Bishops, Knights, and Queens
        break;
    }  // switch

    en_passant_ = false;
    cur_piece->set_pos(new_pos);  // Update piece coordinates
    board_->move(old_pos, new_pos);  // Move piece
    assert(!board_->get_tile(old_pos));  // Old tile should contain nullptr
    switch_turns();  // Switch turns upon successful move
    return true;
}

void Move_maker::print_board(ostream &os) const {
    os << *board_;
}

/*
Move_maker private members
*/

void Move_maker::capture_en_passant_pawn() {
    Piece *&target_tile = board_->get_tile(last_en_passant_pos_);
    delete target_tile;
    target_tile = nullptr;
}

bool Move_maker::collision(const Tile &old_pos, const Tile &new_pos,
    const Direction &direction) const {
    Tile current_tile = old_pos;
    int vert_mvmt, horiz_mvmt;

    // Set vertical movement
    switch (direction) {
    case Direction::N: case Direction::NE: case Direction::NW: {
        vert_mvmt = 1;  // Up if North
        break;
    }
    case Direction::E: case Direction::W: {
        vert_mvmt = 0;  // None if neither North nor South
        break;
    }
    case Direction::S: case Direction::SE: case Direction::SW: {
        vert_mvmt = -1;  // Down if South
        break;
    }
    }

    // Set horizontal movement
    switch (direction) {
    case Direction::E: case Direction::NE: case Direction::SE: {
        horiz_mvmt = 1;  // Right if East
        break;
    }
    case Direction::N: case Direction::S: {
        horiz_mvmt = 0;  // None if neither West nor East
        break;
    }
    case Direction::W: case Direction::NW: case Direction::SW: {
        horiz_mvmt = -1;  // Left if West
        break;
    }
    }

    // Increment b/c don't check start tile
    current_tile.row += vert_mvmt;
    current_tile.col += horiz_mvmt;
    // Scan for collisions
    while (current_tile != new_pos) {
        if (board_->get_tile(current_tile))
            return true;
        // Move in specified direction
        current_tile.row += vert_mvmt;
        current_tile.col += horiz_mvmt;
    }
    return false;
}

void Move_maker::set_king_pos(const King *king) {
    if (king->get_player() == Player::WHITE)
        p1_king_ = king->get_pos();
    else
        p2_king_ = king->get_pos();
}

void Move_maker::castle_update_rook(const Tile &old_pos, const Tile &new_pos) {
    // lambda to move rook to castled position
    static auto move_rook_to_castled = [&](int rook_col, 
        int castled_col) {
        const Tile rook_pos{ old_pos.row, rook_col };
        const Tile castled_pos{ old_pos.row, castled_col };
        Rook *temp_rook = static_cast<Rook *>(board_->get_tile(rook_pos));
        board_->move(rook_pos, castled_pos);
        temp_rook->set_moved();
    };

    if (new_pos.col > old_pos.col)
        // Castle to the right. Adjust right rook.
        move_rook_to_castled(Board::kRightRookInitCol, Board::kRightRookCastledCol);
    else
        // Castle to the left. Adjust left rook.
        move_rook_to_castled(Board::kLeftRookInitCol, Board::kLeftRookCastledCol);
}

bool Move_maker::valid_castle(const King *king, const Tile &new_pos) const {
    if (king->has_moved()) {
        return false;  // Can't castle if already moved
    }
    const Tile cur_pos = king->get_pos();
    assert(cur_pos.col == P1_KING_START.col);  // king should be in starting position

    // lambda to check that rook hasn't moved and no collisions from king to rook
    static auto rook_and_collision_check = [&](const Tile &cur_pos, int rook_col, 
        const Direction direction) {
        // Check corner for rook
        const Tile rook_tile{ cur_pos.row, rook_col };
        const Piece *temp_piece = board_->get_tile(rook_tile);
        if (temp_piece->get_type() == Piece::R) {
            const Rook *temp_rook = static_cast<const Rook *>(temp_piece);
            // Check that rook has not moved and no horizontal collision to the right
            return !(temp_rook->has_moved() || collision(cur_pos, rook_tile, direction));
        }
        return false;
    };

    // Castle right: check right of king
    if (new_pos == Tile{ cur_pos.row, Board::kKingRightCastledCol })
        return rook_and_collision_check(cur_pos, Board::kRightRookInitCol, Direction::E);
    // Castle left: check left of king
    else if (new_pos == Tile{ cur_pos.row, Board::kKingLeftCastledCol })
        return rook_and_collision_check(cur_pos, Board::kLeftRookInitCol, Direction::W);
    // new_pos is not a valid castle tile
    return false;
}

bool Move_maker::valid_move(const Tile &old_pos, const Tile &new_pos) const {
    if (!(board_->tile_in_bounds(new_pos) && board_->tile_in_bounds(old_pos))) {
        cerr << "Input tile is out of bounds\n";
        return false;
    }

    const Piece *cur_piece = board_->get_tile(old_pos);
    const Piece *new_tile = board_->get_tile(new_pos);
    if (!cur_piece)
        return false;  // Player selected empty tile

    // Players move their own pieces
    if (cur_piece->get_player() != turn_) {
        cerr << "Can't move enemy piece\n";
        return false;
    }

    // Can't move onto own piece
    bool capture_own_piece = new_tile ? new_tile->get_player() ==
        cur_piece->get_player() : false;
    if (capture_own_piece) {
        cerr << "Can't capture own piece\n";
        return false;
    }

    // Check physical placement
    bool okay_placement = cur_piece->valid_placement(new_pos);
    // Check unique cases
    //*** TODO: Use virtual functions instead of RTTI-esque switch
    switch (cur_piece->get_type()) {
    case Piece::P: {
        // Pawn capture different than move
        const Piece *target_tile = board_->get_tile(new_pos);
        if (okay_placement) {
            okay_placement = !target_tile;  // If vertical move, make sure target spot is empty
            if (abs(new_pos.row - old_pos.row) == 2) {
                // Check tile one above/below pawn
                Tile one_tile_away{ (old_pos.row + new_pos.row) / 2, old_pos.col };
                // Both tiles clear
                okay_placement = okay_placement && !board_->get_tile(one_tile_away);
            }
        }
        else {
            // Otherwise, check if pawn is capturing an enemy piece
            const Pawn *temp_pawn = static_cast<const Pawn *>(cur_piece);
            Tile en_passant_tile{ old_pos.row, new_pos.col };
            bool possible_en_passant = last_en_passant_pos_ == en_passant_tile;
            // Captured a piece if target tile contains enemy piece OR valid en passant
            bool captured_a_piece = (target_tile && target_tile->get_player() != turn_) ||
                possible_en_passant;
            okay_placement = temp_pawn->valid_capture_placement(new_pos) &&
                captured_a_piece;
            en_passant_ = okay_placement && possible_en_passant;
        }
        break;
    }
    case Piece::B: case Piece::R: case Piece::Q: {
        if (okay_placement) {
            // Check for any pieces between linear piece and target tile
            const LinearPiece *temp_linear_piece = static_cast<const LinearPiece *>(cur_piece);
            Direction move_direction = temp_linear_piece->get_direction(new_pos);
            okay_placement = !collision(old_pos, new_pos, move_direction);
        }
        break;
    }
    case Piece::K: {
        if (!okay_placement) {
            // Check if King is castling
            const King *temp_king = static_cast<const King *>(cur_piece);
            okay_placement = valid_castle(temp_king, new_pos);
        }
        break;
    }
    case Piece::N: {
        // No special case for Knights
        break;
    }
    }
    //*** TODO: Checks on own piece = invalid; checks on enemy piece = update checked_
    return okay_placement;
}