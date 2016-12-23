#ifndef MOVE_MAKER_H
#define MOVE_MAKER_H

#include "board.h"

// TODO: Move stuff over from board? Draw out plan pls

class MoveMaker {
private:
	Board &board_;
public:
	MoveMaker::MoveMaker(Board &board_in)
		: board_{ board_in } {}
	~MoveMaker() {};
};

#endif  // MOVE_MAKER_H
