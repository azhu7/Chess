#include "../include/bishop.h"
#include <iostream>
#include <cassert>

using std::cout;

void bishop_valid_placement_test();

/*int main(int argc, char *argv[]) {
	bishop_valid_placement_test();
	return 0;
}*/

void bishop_valid_placement_test() {
	cout << "Starting bishop valid_placement tests\n";
	Bishop b{ Player::WHITE, Tile{ 2, 2 } };  // 1B @ (2, 2)
	assert(b.valid_placement(Tile{ 2, 2 }));  // Diagonal path to own tile okay
	assert(!b.valid_placement(Tile{ 2, 3 }));  // Horizontal path bad
	assert(!b.valid_placement(Tile{ 3, 2 }));  // Vertical path bad
	assert(b.valid_placement(Tile{ 0, 0 }));
	assert(b.valid_placement(Tile{ 4, 4 }));
	assert(b.valid_placement(Tile{ 0, 4 }));
	assert(b.valid_placement(Tile{ 4, 0 }));
	assert(!b.valid_placement(Tile{ 4, 1 }));
	cout << "All tests passed!\n";
}