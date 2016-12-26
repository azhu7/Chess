#include "player.h"

// Print Player enum as integer value
std::ostream &operator<<(std::ostream &os, const Player p) {
	os << static_cast<std::underlying_type<Player>::type>(p);
	return os;
}