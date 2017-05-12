/**
    Author: Alexander Zhu
    Date Created: May 11, 2017
    Description: Implementation for Knight piece
*/

#include "Knight.h"

#include <cmath>

using std::abs;

bool Knight::valid_physical_placement(Tile new_pos) const {
    const int row_abs_diff = abs(new_pos.row - get_row());
    const int col_abs_diff = abs(new_pos.col - get_col());
    return (row_abs_diff == 1 && col_abs_diff == 2) ||
        (row_abs_diff == 2 && col_abs_diff == 1);
}