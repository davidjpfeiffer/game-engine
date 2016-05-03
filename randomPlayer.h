#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

#include <time.h> 

#include "player.h"
#include "utilities.h"

class RandomPlayer : public Player
{
	public:
	
	Board getMove(const Board & board)
	{
		Board newBoard;
		
		do
		{
			newBoard = copyBoard(board);
			newBoard[getRandomNumber(3)][getRandomNumber(3)] = this->getPlayerBoardValue();
		} while(!validMove(board, newBoard, this->getPlayerBoardValue()));
		
		return newBoard;
	}
};

#endif