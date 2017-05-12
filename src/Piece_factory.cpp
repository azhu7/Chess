/**
    Author: Alexander Zhu
    Date Created: April 12, 2017
    Description: Implementation for Piece factory
*/

#include "Piece_factory.h"

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Utility.h"

// Allocates and initializes piece based on supplied information. Throws error
// on invalid type.
Piece *create_piece(Player player, Tile pos, Piece::PieceType type) {
    switch (type) {
    case Piece::P: return new Pawn{ player, pos };
    case Piece::N: return new Knight{ player, pos };
    case Piece::B: return new Bishop{ player, pos };
    case Piece::R: return new Rook{ player, pos };
    case Piece::Q: return new Queen{ player, pos };
    case Piece::K: return new King{ player, pos };
    }
    throw Error{ "Invalid Piece Type " + type + '\n' };
}
