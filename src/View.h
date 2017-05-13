#ifndef VIEW_H
#define VIEW_H

#include "Tile.h"

#include <iostream>
#include <map>
#include <string>

class View {
public:
    // Pretty print the board
    void draw(std::ostream &ofs = std::cout) const;

    // Associate id with new position.
    void update_position(const std::string &id, Tile pos) {
        piece_positions[pos] = id;
    }

    // Associate id with new position. Forget its old position.
    void update_move(const std::string &id, Tile old_pos, Tile new_pos) {
        piece_positions.erase(old_pos);
        piece_positions[new_pos] = id;
    }

    // Disassociate id from position.
    void update_remove(Tile pos) {
        piece_positions.erase(pos);
    }

private:
    struct Tile_comp {
        bool operator()(Tile t1, Tile t2) const {
            if (t1.row == t2.row)
                return t1.col < t2.col;
            return t1.row < t2.row;
        }
    };
    // Map from Tile to string as pieces can have the same name.
    std::map<Tile, std::string, Tile_comp> piece_positions;
};

#endif  // !VIEW_H
