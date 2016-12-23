/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Player enum
*
*  TODO: Implement functions all in .h file?
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

enum class Player : char {
	WHITE = '1',
	BLACK = '2'
};

// Print Player as integer value
std::ostream &operator<<(std::ostream &os, const Player p);

#endif  // PLAYER_H