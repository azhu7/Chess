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
Piece *create_piece(Player player, Tile pos, char type) {
    switch (type) {
    case 'P': return new Pawn{ player, pos };
    case 'N': return new Knight{ player, pos };
    case 'B': return new Bishop{ player, pos };
    case 'R': return new Rook{ player, pos };
    case 'Q': return new Queen{ player, pos };
    case 'K': return new King{ player, pos };
    }
    throw Error{ "Invalid Piece Type " + type + '\n' };
}
