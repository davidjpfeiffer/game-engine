#include "utilities.h"

#ifndef __PLAYER
#define __PLAYER

class Player
{
	public:
	
	virtual void setNumber(BoardValue playerBoardValue) = 0;
	virtual BoardValue getNumber() = 0;
	virtual IBoard getMove(const IBoard &) = 0;
};

#endif