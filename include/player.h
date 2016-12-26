/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Player enum
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

enum class Player : char {
	WHITE = '1',
	BLACK = '2'
};

// Print Player as integer value
static std::ostream &operator<<(std::ostream &os, const Player p) {
	os << static_cast<std::underlying_type<Player>::type>(p);
	return os;
}

#endif  // PLAYER_H