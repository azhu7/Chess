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
    virtual ~Piece() {}

    // Getters
    const Player &get_player() const { return color; }
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

    // REQUIRES pos is a valid coordinate
    // EFFECTS  Determine if piece is physically allowed to move to new position.
    //          Does not take into account other pieces at that position or along
    //          the way.
    virtual bool valid_placement(Tile new_pos) const = 0;

    // Output operator overloads
    friend std::ostream &operator<<(std::ostream &os, Piece::PieceType pt);
    friend std::ostream &operator<<(std::ostream &os, const Piece *p);

protected:
    explicit Piece(Player color_, Tile pos_)
        : color{ color_ }, pos{ pos_ } {}

private:
    Player color;
    Tile pos;
};

#endif  // !PIECE_H