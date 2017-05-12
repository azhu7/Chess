/**
    Author: Alexander Zhu
    Date Created: May 11, 2017
    Description: Implementation for Chess Utility
*/

#include "Utility.h"

#include "Board.h"
#include "Tile.h"

bool collision(Tile old_pos, Tile new_pos, Direction direction) {
    Tile current_tile = old_pos;
    int vert_mvmt, horiz_mvmt;

    // Set vertical movement
    switch (direction) {
    case Direction::N: case Direction::NE: case Direction::NW: {
        vert_mvmt = 1;  // Up if North
        break;
    }
    case Direction::E: case Direction::W: {
        vert_mvmt = 0;  // None if neither North nor South
        break;
    }
    case Direction::S: case Direction::SE: case Direction::SW: {
        vert_mvmt = -1;  // Down if South
        break;
    }
    }

    // Set horizontal movement
    switch (direction) {
    case Direction::E: case Direction::NE: case Direction::SE: {
        horiz_mvmt = 1;  // Right if East
        break;
    }
    case Direction::N: case Direction::S: {
        horiz_mvmt = 0;  // None if neither West nor East
        break;
    }
    case Direction::W: case Direction::NW: case Direction::SW: {
        horiz_mvmt = -1;  // Left if West
        break;
    }
    }

    // Increment b/c don't check start tile
    current_tile.row += vert_mvmt;
    current_tile.col += horiz_mvmt;
    // Scan for collisions
    while (current_tile != new_pos) {
        if (Board::get_instance().get_tile(current_tile))
            return true;
        // Move in specified direction
        current_tile.row += vert_mvmt;
        current_tile.col += horiz_mvmt;
    }
    return false;
}
