/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Implementation for Player enum
*/

#include "Player.h"

#include <ostream>

using std::ostream;
using std::underlying_type;

ostream &operator<<(ostream &os, Player p) {
    return os << static_cast<underlying_type<Player>::type>(p);
}