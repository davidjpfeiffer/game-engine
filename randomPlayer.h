#include <cstdlib>
#include <time.h> 

#include "player.h"
#include "utilities.h"

#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

class RandomPlayer : public Player
{
	private:
	
	BoardValue playerBoardValue;
	
	unsigned getRandomNumber(unsigned mod)
	{
		return rand() % mod;
	}
	
	public:
	
	RandomPlayer()
	{
		srand(time(NULL));
	}
	
	void setNumber(BoardValue playerBoardValue)
	{
		this->playerBoardValue = playerBoardValue;
	}
	
	BoardValue getNumber()
	{
		return this->playerBoardValue;
	}
	
	IBoard getMove(const IBoard & board)
	{
		IBoard newBoard;
		
		do
		{
			newBoard = copyBoard(board);
			newBoard[getRandomNumber(3)][getRandomNumber(3)] = playerBoardValue;
		} while(!validMove(board, newBoard, this->playerBoardValue));
		
		return newBoard;
	}
};

#endif