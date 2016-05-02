#include <cstdlib>
#include <time.h> 

#include "player.h"
#include "utilities.h"

#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

class RandomPlayer : public Player
{
	unsigned getRandomNumber(unsigned mod)
	{
		return rand() % mod;
	}
	
	public:
	
	RandomPlayer()
	{
		srand(time(NULL));
	}
	
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