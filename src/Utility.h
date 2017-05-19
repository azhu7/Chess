/**
    Author: Alexander Zhu
    Date Created: March 31, 2017
    Description: Header file for Chess Utility
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <ios>

struct Tile;

class Error : public std::exception {
public:
    Error(const char *msg_) : msg{ msg_ } {}
    const char *what() const noexcept override { return msg; }

private:
    const char *msg;
};

enum class Direction {
    N, S, E, W, NE, NW, SE, SW
};

// Skip remainder of input stream line
void skip_line();

// Check for any pieces between old_pos and new_pos. Requires straight path 
// from current pos to new_pos.
bool collision(Tile old_pos, Tile new_pos, Direction direction);

#endif  // !UTILITY_H