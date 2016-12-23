#ifndef UTIL_H
#define UTIL_H

#include "tile.h"

namespace util {
	// EFFECTS  Return true if linear path from old pos to new pos
	//			Used by Bishop, Rook, and Queen
	bool linear_path(const Tile &old_pos, const Tile &new_pos);
}

#endif  // UTIL_H