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

#include <string>

using std::string;
using std::shared_ptr; using std::make_shared;

// Allocates and initializes piece based on supplied information. Throws error
// on invalid type.
shared_ptr<Piece> create_piece(Player player, Tile pos, char type) {
    string id{ string{} + (char)('0' + player) + type };  // Example: 1P
    switch (type) {
    case 'P': return make_shared<Pawn>(id, player, pos);
    case 'N': return make_shared<Knight>(id, player, pos);
    case 'B': return make_shared<Bishop>(id, player, pos);
    case 'R': return make_shared<Rook>(id, player, pos);
    case 'Q': return make_shared<Queen>(id, player, pos);
    case 'K': return make_shared<King>(id, player, pos);
    }
    throw Error{ "Invalid piece type!" };
}
