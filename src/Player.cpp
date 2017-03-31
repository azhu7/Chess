#include "../include/player.h"

std::ostream &operator<<(std::ostream &os, Player p) {
    return os << static_cast<std::underlying_type<Player>::type>(p);
}