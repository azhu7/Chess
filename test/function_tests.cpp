#include "../include/bishop.h"
#include "../include/queen.h"
#include "../include/knight.h"
#include "../include/king.h"
#include <iostream>
#include <cassert>

using std::cout;

void bishop_valid_placement_test();
void queen_valid_placement_test();
void knight_valid_placement_test();

int main(int argc, char *argv[]) {
	cout << "Begin testing.\n";
	bishop_valid_placement_test();
	queen_valid_placement_test();
	knight_valid_placement_test();
	cout << "All tests passed!\n";
	return 0;
}

// Simple test for Bishop::valid_placement
void bishop_valid_placement_test() {
	cout << "Starting bishop valid_placement test\n";
	Bishop b{ Player::WHITE, Tile{ 2, 2 } };  // 1B @ (2, 2)
	assert(!b.valid_placement(Tile{ 2, 2 }));  // Diagonal path to own tile not okay
	assert(!b.valid_placement(Tile{ 2, 3 }));  // Horizontal path bad
	assert(!b.valid_placement(Tile{ 3, 2 }));  // Vertical path bad
	assert(b.valid_placement(Tile{ 0, 0 }));  // Diagonal okay
	assert(b.valid_placement(Tile{ 4, 4 }));  // Diagonal okay
	assert(b.valid_placement(Tile{ 0, 4 }));  // Diagonal okay
	assert(b.valid_placement(Tile{ 4, 0 }));  // Diagonal okay
	assert(!b.valid_placement(Tile{ 4, 1 }));  // Non-diagonal not okay
	cout << "Bueen valid_placement test passed!\n";
}

// Simple test for Queen::valid_placement
void queen_valid_placement_test() {
	cout << "Starting queen valid_placement test\n";
	Queen q{ Player::WHITE, Tile{ 3, 3 } };  // 1Q @ (3, 3)
	assert(!q.valid_placement(Tile{ 3, 3 }));  // Path to own tile not okay
	assert(q.valid_placement(Tile{ 3, 2 }));  // Horizontal path okay
	assert(q.valid_placement(Tile{ 2, 3 }));  // Vertical path okay
	assert(q.valid_placement(Tile{ 0, 0 }));  // Diagonal okay
	assert(q.valid_placement(Tile{ 2, 4 }));  // Diagonal okay
	assert(!q.valid_placement(Tile{ 0, 4 }));  // Nonlinear not okay
	assert(!q.valid_placement(Tile{ 4, 0 }));  // Nonlinear not okay
	assert(!q.valid_placement(Tile{ 4, 1 }));  // Nonlinear not okay
	cout << "Queen valid_placement test passed!\n";
}

void knight_valid_placement_test() {
	cout << "Starting knight valid_placement test\n";
	Knight n{ Player::WHITE, Tile{3, 3} };  // 1N @ (3, 3)
	assert(!n.valid_placement(Tile{ 3, 3 }));  // Path to own tile not okay
	assert(n.valid_placement(Tile{ 5, 4 }));  // L-shaped okay
	assert(n.valid_placement(Tile{ 2, 5 }));  // L-shaped okay
	assert(n.valid_placement(Tile{ 4, 1 }));  // L-shaped okay
	assert(!n.valid_placement(Tile{ 2, 3 }));  // Non-L not okay
	assert(!n.valid_placement(Tile{ 6, 3 }));  // Non-L not okay
	assert(!n.valid_placement(Tile{ 4, 4 }));  // Non-L not okay
	assert(!n.valid_placement(Tile{ 5, 5 }));  // Non-L not okay
	cout << "Knight valid_placement test passed!\n";
}