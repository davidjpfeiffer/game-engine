#ifndef __GAME
#define __GAME

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "utilities.h"
#include "player.h"

class Game
{
	public:
	
	Game(Player & playerOne, Player & playerTwo)
	{
		playerOne.setPlayerBoardValue(BoardValue::O);
		playerTwo.setPlayerBoardValue(BoardValue::X);
		
		this->currentPlayer = & playerOne;
		this->playerOne = & playerOne;
		this->playerTwo = & playerTwo;
		this->board = createNewBoard();
	}
	
	void play()
	{
		switch(getGameResult())
		{
			case GameResult::PlayerOneWin:
				std::cout << "Result Of game: Player One Wins!\n";
				break;
			
			case GameResult::PlayerTwoWin:
				std::cout << "Result Of game: Player Two Wins!\n";
				break;
			
			case GameResult::Tie:
				std::cout << "Result Of Game: Tie!\n";
				break;
			
			default:
				std::cout << "An error occured.\n";
				break;
		}
	}
	
	private:
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	GameSettings settings;
	
	GameResult getGameResult()
	{
		printBoard(board);
		
		while(!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
		{
			Board boardAfterPlayerMove = this->currentPlayer->getMove(board);
			
			if (validMove(board, boardAfterPlayerMove, this->currentPlayer->getPlayerBoardValue()))
			{
				board = copyBoard(boardAfterPlayerMove);
				toggleCurrentPlayer();
				sleep(1);
				printBoard(board);
			}
			else
			{
				std::cout << "Player did not submit a valid move.";
				exit(0);
			}
		}
		
		if(playerHasWon(board, this->playerOne->getPlayerBoardValue())) return GameResult::PlayerOneWin;
		else if (playerHasWon(board, this->playerTwo->getPlayerBoardValue())) return GameResult::PlayerTwoWin;
		else return GameResult::Tie;
	}
	
	toggleCurrentPlayer()
	{
		this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
	}
};

#endif