#include "Player.h"

// Print Player enum as integer value
std::ostream &operator<<(std::ostream &os, const Player p) {
	os << static_cast<std::underlying_type<Player>::type>(p);
	return os;
}

// Return Player enum as string value
std::string player_to_string(const Player p) {
	return p == Player::WHITE ? std::string{ "Player 1" } : std::string{ "Player 2" };
}