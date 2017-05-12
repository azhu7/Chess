/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Header file for abstract piece
*/

#ifndef PIECE_H
#define PIECE_H

#include "Player.h"
#include "Tile.h"

class Piece {
public:
    explicit Piece(Player color_, Tile pos_)
        : player{ color_ }, pos{ pos_ } {}

    virtual ~Piece() {}

    // Getters
    const Player &get_player() const { return player; }
    int get_row() const { return pos.row; }
    int get_col() const { return pos.col; }

    // EFFECTS  Returns piece position as Tile. Useful for passing into functions.
    const Tile get_pos() const { return pos; }

    void set_pos(Tile pos_) { pos = pos_; }

    enum PieceType : char {
        P = 'P', B = 'B', N = 'N', R = 'R', Q = 'Q', K = 'K'
    };

    // EFFECTS  Return piece type
    virtual PieceType get_type() const = 0;

    // Determine if piece can move to new position. Utilizes Template Method
    // and Non-virtual Interface patterns to customize behavior.
    bool valid_move(Tile new_pos) const;

    // Output operator overloads
    friend std::ostream &operator<<(std::ostream &os, Piece::PieceType pt);
    friend std::ostream &operator<<(std::ostream &os, Piece *p);

protected:
    // Determine if this Piece is physically allowed to move to new position.
    // Does not take into account other pieces at that position or along the way.
    virtual bool valid_physical_placement(Tile new_pos) const = 0;

    // Depending on if physical placement was valid, check other rules for 
    // moving this Piece. Behavior varies by Derived type. Returns 
    // valid_placement by default.
    virtual bool additional_placement_checks(bool valid_physical_placement,
        Tile new_pos) const { return valid_physical_placement; }

private:
    Player player;
    Tile pos;
};

#endif  // !PIECE_H