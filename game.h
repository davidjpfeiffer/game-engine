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
		
		this->playerOneWins = 0;
		this->playerTwoWins = 0;
		this->gamesTied = 0;
	}
	
	void play()
	{
		for(unsigned gameNumber = 1; gameNumber <= this->gameSettings.numberOfGames; gameNumber++)
		{
			this->board = createNewBoard();
			
			switch(getGameResult())
			{
				case GameResult::PlayerOneWin:
					if (this->gameSettings.displayEachGameResult) std::cout << "Result Of game: " << gameNumber << ": Player One Wins!\n";
					this->playerOneWins++;
					break;
				
				case GameResult::PlayerTwoWin:
					if (this->gameSettings.displayEachGameResult) std::cout << "Result Of game: " << gameNumber << ": Player Two Wins!\n";
					this->playerTwoWins++;
					break;
				
				case GameResult::Tie:
					if (this->gameSettings.displayEachGameResult) std::cout << "Result Of game: " << gameNumber << ": Tie!\n";
					this->gamesTied++;
					break;
				
				default:
					std::cout << "An error occured.\n";
					break;
			}
		}
		
		if (this->gameSettings.displayStatistics) displayStatistics();
	}
	
	struct GameSettings
	{
		bool displayMoves = true;
		bool displayStatistics = false;
		bool displayEachGameResult = true;
		unsigned delayBetweenMoves = 1;
		unsigned numberOfGames = 1;
	} gameSettings;
	
	private:
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	unsigned playerOneWins, playerTwoWins, gamesTied;
	
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
	
	displayStatistics()
	{
		std::cout << "------------------------------\n";
		std::cout << "Game Statistics\n";
		std::cout << "Player One Wins: " << this->playerOneWins << '\n';
		std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
		std::cout << "Games Tied: " << this->gamesTied << '\n';
		std::cout << "Total Number Of Games: " << this->gameSettings.numberOfGames << '\n';
		std::cout << "------------------------------\n";
	}
};

#endif