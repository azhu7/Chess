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

using std::shared_ptr; using std::make_shared;

// Allocates and initializes piece based on supplied information. Throws error
// on invalid type.
shared_ptr<Piece> create_piece(Player player, Tile pos, char type) {
    switch (type) {
    case 'P': return make_shared<Pawn>(player, pos);
    case 'N': return make_shared<Knight>(player, pos);
    case 'B': return make_shared<Bishop>(player, pos);
    case 'R': return make_shared<Rook>(player, pos);
    case 'Q': return make_shared<Queen>(player, pos);
    case 'K': return make_shared<King>(player, pos);
    }
    throw Error{ "Invalid Piece Type " + type + '\n' };
}
