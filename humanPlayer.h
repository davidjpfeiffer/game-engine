#include "player.h"
#include "utilities.h"
#include <iostream>

#ifndef __HUMANPLAYER
#define __HUMANPLAYER

class HumanPlayer : public Player
{
	private:
	
	BoardValue playerBoardValue;
	
	public:
	
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
		bool validMoveMade = false;
		unsigned row, column;
		
		std::cout << "Player " << this->playerBoardValue << "s turn\n";
		
		while(!validMoveMade)
		{
			std::cout << "Enter the row: ";
			std::cin >> row;
			
			std::cout << "Enter the column: ";
			std::cin >> column;
			
			newBoard = copyBoard(board);
			
			if(row > 0 && row < 4 && column > 0 && column < 4) newBoard[row - 1][column - 1] = playerBoardValue;
			else std::cout << "Row and column must be between 1 and 3!\n";
			
			validMoveMade = validMove(board, newBoard, this->playerBoardValue);
			if (!validMoveMade) std::cout << "That was not a valid move. Please try again.\n";
		}
		
		return newBoard;
	}
};

#endif