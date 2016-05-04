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
		
		this->playerOne = & playerOne;
		this->playerTwo = & playerTwo;
		this->currentPlayer = this->playerOne;
		
		this->board = createNewBoard();
	}
	
	void play()
	{
		for(unsigned gameNumber = 1; gameNumber <= this->gameSettings.numberOfGames; gameNumber++)
		{
			switch(getGameResult())
			{
				case GameResult::PlayerOneWin:
					std::cout << "Result Of game: " << gameNumber << ": Player One Wins!\n";
					break;
				
				case GameResult::PlayerTwoWin:
					std::cout << "Result Of game: " << gameNumber << ": Player Two Wins!\n";
					break;
				
				case GameResult::Tie:
					std::cout << "Result Of game: " << gameNumber << ": Tie!\n";
					break;
				
				default:
					std::cout << "An error occured.\n";
					break;
			}
		}
	}
	
	struct GameSettings
	{
		bool displayMoves = false;
		unsigned delayBetweenMoves = 1;
		unsigned numberOfGames = 10;
	} gameSettings;
	
	private:
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	
	GameResult getGameResult()
	{
		if (this->gameSettings.displayMoves) printBoard(board);
		
		while(!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
		{
			Board boardAfterPlayerMove = this->currentPlayer->getMove(board);
			
			if (validMove(board, boardAfterPlayerMove, this->currentPlayer->getPlayerBoardValue()))
			{
				board = copyBoard(boardAfterPlayerMove);
				toggleCurrentPlayer();
				if (this->gameSettings.displayMoves)
				{
					sleep(this->gameSettings.delayBetweenMoves);
					printBoard(board);
				}
			}
			else
			{
				std::cout << "Player " << this->currentPlayer->getPlayerBoardValue() << " did not submit a valid move.";
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