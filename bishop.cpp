#include "bishop.h"
#include "util.h"

using namespace util;

bool Bishop::valid_placement(const Tile &pos) const {
	return linear_path(get_pos(), pos);
}