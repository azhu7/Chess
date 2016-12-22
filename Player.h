/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Player enum
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

enum class Player : int {
	WHITE = 1,
	BLACK = 2
};

// Print Player enum as integer value
std::ostream &operator<<(std::ostream &os, const Player p);

// Return Player enum as string value
std::string player_to_string(const Player p);

#endif  // PLAYER_H