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
Piece *create_piece(Player color, Tile pos, Piece::PieceType type) {
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
