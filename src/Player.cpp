#include "Player.h"

#include <ostream>

using std::ostream;
using std::underlying_type;

ostream &operator<<(ostream &os, Player p) {
    return os << static_cast<underlying_type<Player>::type>(p);
}