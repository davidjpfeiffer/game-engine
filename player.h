#include "utilities.h"

#ifndef __PLAYER
#define __PLAYER

class Player
{
	private:
	
	BoardValue playerBoardValue;
	BoardValue opponentBoardValue;
	
	public:
	
	virtual Board getMove(const Board &) = 0;
	
	void setPlayerBoardValue(BoardValue playerBoardValue)
	{
		this->playerBoardValue = playerBoardValue;
		this->opponentBoardValue = this->playerBoardValue == BoardValue::X ? BoardValue::O : BoardValue::X;
	}
	
	BoardValue getPlayerBoardValue()
	{
		return this->playerBoardValue;
	}
	
	BoardValue getOpponentBoardValue()
	{
		return this->playerBoardValue;
	}
};

#endif