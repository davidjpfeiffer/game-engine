#include <cstdlib>
#include <time.h> 

#include "player.h"
#include "utilities.h"

#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER

class ComputerPlayer : public Player
{
	private:
	
	BoardValue playerBoardValue;
	BoardValue opponentBoardValue;
	
	unsigned getRandomNumber(unsigned mod)
	{
		return rand() % mod;
	}
	
	public:
	
	ComputerPlayer()
	{
		srand(time(NULL));
	}
	
	void setNumber(BoardValue playerBoardValue)
	{
		this->playerBoardValue = playerBoardValue;
		this->opponentBoardValue = this->playerBoardValue == BoardValue::X ? BoardValue::O : BoardValue::X;
	}
	
	BoardValue getNumber()
	{
		return this->playerBoardValue;
	}
	
	IBoard getMove(const IBoard & board)
	{
		IBoard mainBoard = copyBoard(board);
		IBoard theoreticalBoard, defaultBoard;
		
		// If we can win, take win
		for(unsigned i = 0; i < BOARD_SIZE; i++)
		{
			for(unsigned j = 0; j < BOARD_SIZE; j++)
			{
				theoreticalBoard = copyBoard(board);
				if(theoreticalBoard[i][j] == BoardValue::Empty)
				{
					theoreticalBoard[i][j] = this->playerBoardValue;
					if (playerHasWon(theoreticalBoard, this->playerBoardValue))
					{
						mainBoard[i][j] = this->playerBoardValue;
						return mainBoard;
					}
				}
				
			}
		}
		
		// If they can win, prevent win
		for(unsigned i = 0; i < BOARD_SIZE; i++)
		{
			for(unsigned j = 0; j < BOARD_SIZE; j++)
			{
				theoreticalBoard = copyBoard(board);
				if(theoreticalBoard[i][j] == BoardValue::Empty)
				{
					theoreticalBoard[i][j] = this->opponentBoardValue;
					if (playerHasWon(theoreticalBoard, this->opponentBoardValue))
					{
						mainBoard[i][j] = this->playerBoardValue;
						return mainBoard;
					}
				}
				
			}
		}
		
		// If middle available, take middle
		if (mainBoard[1][1] == BoardValue::Empty)
		{
			mainBoard[1][1] = this->playerBoardValue;
			return mainBoard;
		}
		
		// Offensive
		if (mainBoard[1][1] == this->playerBoardValue && numAvailableMoves(board) == 7)
		{
			if (mainBoard[0][1] == this->opponentBoardValue)
			{
				mainBoard[2][2] = this->playerBoardValue;
				return mainBoard;
			} else if (mainBoard[1][2] == this->opponentBoardValue)
			{
				mainBoard[2][0] = this->playerBoardValue;
				return mainBoard;
			}
			else if (mainBoard[2][1] == this->opponentBoardValue)
			{
				mainBoard[0][0] = this->playerBoardValue;
				return mainBoard;
			}
			else if (mainBoard[1][0] == this->opponentBoardValue)
			{
				mainBoard[2][2] = this->playerBoardValue;
				return mainBoard;
			}
		}
		
		// If corner available, take corner
		if (mainBoard[0][0] == BoardValue::Empty)
		{
			mainBoard[0][0] = this->playerBoardValue;
			return mainBoard;
		}
		else if (mainBoard[0][2] == BoardValue::Empty)
		{
			mainBoard[0][2] = this->playerBoardValue;
			return mainBoard;
		}
		else if (mainBoard[2][0] == BoardValue::Empty)
		{
			mainBoard[2][0] = this->playerBoardValue;
			return mainBoard;
		}
		else if (mainBoard[2][2] == BoardValue::Empty)
		{
			mainBoard[2][2] = this->playerBoardValue;
			return mainBoard;
		}
		
		// Default to random move
		do
		{
			defaultBoard = copyBoard(board);
			defaultBoard[getRandomNumber(3)][getRandomNumber(3)] = playerBoardValue;
		} while(!validMove(board, defaultBoard, this->playerBoardValue));
		
		return defaultBoard;
	}
};

#endif