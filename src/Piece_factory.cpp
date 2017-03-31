#include "Piece_factory.h";

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Utility.h"

Piece *create_piece(const Player color, const Tile &pos, const Piece::PieceType type) {
    switch (type) {
    case Piece::P: return new Pawn{ color, pos };
    case Piece::N: return new Knight{ color, pos };
    case Piece::B: return new Bishop{ color, pos };
    case Piece::R: return new Rook{ color, pos };
    case Piece::Q: return new Queen{ color, pos };
    case Piece::K: return new King{ color, pos };
    }
    throw Error{ "Invalid Piece Type " + type + '\n' };
}