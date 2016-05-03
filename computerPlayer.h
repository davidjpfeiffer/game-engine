#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER

#include <cstdlib>
#include <time.h> 

#include "player.h"
#include "utilities.h"

class ComputerPlayer : public Player
{
	public:
	
	Board getMove(const Board & board)
	{
		Board mainBoard = copyBoard(board);
		Board theoreticalBoard, defaultBoard;
		
		// If we can win, take win
		for(unsigned i = 0; i < BOARD_SIZE; i++)
		{
			for(unsigned j = 0; j < BOARD_SIZE; j++)
			{
				theoreticalBoard = copyBoard(board);
				if(theoreticalBoard[i][j] == BoardValue::Empty)
				{
					theoreticalBoard[i][j] = this->getPlayerBoardValue();
					if (playerHasWon(theoreticalBoard, this->getPlayerBoardValue()))
					{
						mainBoard[i][j] = this->getPlayerBoardValue();
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
					theoreticalBoard[i][j] = this->getOpponentBoardValue();
					if (playerHasWon(theoreticalBoard, this->getOpponentBoardValue()))
					{
						mainBoard[i][j] = this->getPlayerBoardValue();
						return mainBoard;
					}
				}
				
			}
		}
		
		// If middle available, take middle
		if (mainBoard[1][1] == BoardValue::Empty)
		{
			mainBoard[1][1] = this->getPlayerBoardValue();
			return mainBoard;
		}
		
		// Offensive Strategy
		if (mainBoard[1][1] == this->getPlayerBoardValue() && numAvailableMoves(board) == 7)
		{
			if (mainBoard[0][1] == this->getOpponentBoardValue())
			{
				mainBoard[2][2] = this->getPlayerBoardValue();
				return mainBoard;
			} else if (mainBoard[1][2] == this->getOpponentBoardValue())
			{
				mainBoard[2][0] = this->getPlayerBoardValue();
				return mainBoard;
			}
			else if (mainBoard[2][1] == this->getOpponentBoardValue())
			{
				mainBoard[0][0] = this->getPlayerBoardValue();
				return mainBoard;
			}
			else if (mainBoard[1][0] == this->getOpponentBoardValue())
			{
				mainBoard[2][2] = this->getPlayerBoardValue();
				return mainBoard;
			}
		}
		
		// If corner available, take corner
		if (mainBoard[0][0] == BoardValue::Empty)
		{
			mainBoard[0][0] = this->getPlayerBoardValue();
			return mainBoard;
		}
		else if (mainBoard[0][2] == BoardValue::Empty)
		{
			mainBoard[0][2] = this->getPlayerBoardValue();
			return mainBoard;
		}
		else if (mainBoard[2][0] == BoardValue::Empty)
		{
			mainBoard[2][0] = this->getPlayerBoardValue();
			return mainBoard;
		}
		else if (mainBoard[2][2] == BoardValue::Empty)
		{
			mainBoard[2][2] = this->getPlayerBoardValue();
			return mainBoard;
		}
		
		// Default to random move
		do
		{
			defaultBoard = copyBoard(board);
			defaultBoard[getRandomNumber(3)][getRandomNumber(3)] = this->getPlayerBoardValue();
		} while(!validMove(board, defaultBoard, this->getPlayerBoardValue()));
		
		return defaultBoard;
	}
};

#endif