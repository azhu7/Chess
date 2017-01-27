/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Header file for Player enum
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>

enum class Player : char {
    WHITE = '1',
    BLACK = '2'
};

// Print Player as char value
std::ostream &operator<<(std::ostream &os, const Player p);

#endif  // PLAYER_H