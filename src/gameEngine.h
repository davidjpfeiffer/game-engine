#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "utilities.h"
#include "player.h"

class GameEngine
{
	public:
	
	GameEngine(Player & playerOne, Player & playerTwo)
	{
		playerOne.setPlayerBoardValue(BoardValue::O);
		playerTwo.setPlayerBoardValue(BoardValue::X);
		
		this->playerOne = & playerOne;
		this->playerTwo = & playerTwo;
		this->currentPlayer = this->playerOne;
	}
	
	virtual void play() = 0;
	
	struct GameSettings
	{
		GameType gameType;
		unsigned numberOfGames;
	} gameSettings;
	
	protected:
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	
	void toggleCurrentPlayer()
	{
		this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
	}
};

#endif