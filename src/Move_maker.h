/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for MoveMaker. Enforces chess rules for moving 
                 pieces.
*/

#ifndef MOVE_MAKER_H
#define MOVE_MAKER_H

#include "Linear_piece.h"

#include <iosfwd>

class Board;
class King;

// REQUIRES User must initialize MoveMaker with a Board object. This way, the
//          user can load different piece layouts.
// EXAMPLE  Board board;
//          MoveMaker move_maker{ board };
class Move_maker {
public:
    explicit Move_maker(Board *board_);
    ~Move_maker() {}

    // EFFECTS  Return current player
    const Player &get_current_player() const { return turn; }

    // MODIFIES board_
    // EFFECTS  Move piece to new tile if valid move, otherwise return false
    //*** TODO     Update to return different enum codes?
    bool make_move(Tile old_pos, Tile new_pos);

    void print_board(std::ostream &os) const;

private:
    using Direction = LinearPiece::Direction;
    Board *board;
    Tile p1_king;  // Track each player's king to help with check detection
    Tile p2_king;
    Tile last_en_passant_pos;  // Track tile of pawn that moved two ranks last move. 
                                // {-1, -1} if none.
    Player turn;
    mutable bool en_passant;  // True if current move is an en_passant. Used to
                              // communicate between valid_move() and make_move()
    //Player checked_;  // Player whose King is under attack
                        // Check detection not yet implemented

    // MODIFIES turn_
    // EFFECTS  Updates whose turn it is. Called by make_move()
    void switch_turns() {
        turn = turn == Player::WHITE ? Player::BLACK : Player::WHITE;
    }

    // MODIFIES board_
    // EFFECTS  Remove en passant pawn from board_
    void capture_en_passant_pawn();

    // REQUIRES Straight path from current pos to new_pos
    // EFFECTS  Check for any pieces between old_pos and new_pos
    bool collision(Tile old_pos, Tile new_pos, Direction direction) const;

    // MODIFIES p1_king or p2_king depending on which player king belongs to
    // EFFECTS  Update the king's position as tracked by MoveMaker
    void set_king_pos(const King *king);

    // MODIFIES rook, board_
    // EFFECTS  Moves rook to correct castle position. Called by make_move()
    void castle_update_rook(Tile old_pos, Tile new_pos);

    // REQUIRES cur_pos is coordinate of a King piece
    // EFFECTS  Check if king can castle to new_pos
    bool valid_castle(const King *king, Tile new_pos) const;

    // EFFECTS  Determine if piece can be moved to new tile.
    //          Make sure piece moves according to Chess rules.
    bool valid_move(Tile old_pos, Tile new_pos) const;

    // EFFECTS  Upon a successful move, detect any checks
    //*** TODO     Accomplish by checking around King?
    bool detect_check() const;

    // EFFECTS  Upon a check, detect checkmate
    bool detect_checkmate() const;
};

#endif  // !MOVE_MAKER_H
