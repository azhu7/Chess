#include "util.h"

namespace util {
	bool linear_path(const Tile &old_pos, const Tile &new_pos) {
		// Same column or row
		if (new_pos.col == old_pos.col || new_pos.row == old_pos.row) {
			return true;
		}
		return false;
	}
}