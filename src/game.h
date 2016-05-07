#ifndef __GAME
#define __GAME

#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "gameEngine.h"

class Game : public GameEngine
{
	public:
	
	Game(Player & playerOne, Player & playerTwo) : GameEngine(playerOne, playerTwo)
	{
		this->gameSettings.gameType = GameType::Single;
		this->gameSettings.delayBetweenMoves = 1;
		this->gameSettings.numberOfGames = 1;
	}
	
	void play()
	{
		for(unsigned gameNumber = 1; gameNumber <= this->gameSettings.numberOfGames; gameNumber++)
		{
			resetBoard();
			
			switch(getGameResult())
			{
				case GameResult::PlayerOneWin:
					if (this->gameSettings.gameType == GameType::Single)
						std::cout << "Result Of game " << gameNumber << ": Player One Wins!\n";
					this->playerOneWins++;
					break;
				
				case GameResult::PlayerTwoWin:
					if (this->gameSettings.gameType == GameType::Single)
						std::cout << "Result Of game " << gameNumber << ": Player Two Wins!\n";
					this->playerTwoWins++;
					break;
				
				case GameResult::Tie:
					if (this->gameSettings.gameType == GameType::Single)
						std::cout << "Result Of game " << gameNumber << ": Tie!\n";
					this->gamesTied++;
					break;
			}
		}
		
		if (this->gameSettings.gameType == GameType::Multiple) displayStatistics();
	}
	
	private:
	
	unsigned playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
	
	GameResult getGameResult()
	{
		if (this->gameSettings.gameType == GameType::Single) printBoard(this->board);
		
		while(!boardIsInWinningState(this->board) && numAvailableMoves(this->board) > 0)
		{
			Board boardAfterPlayerMove = this->currentPlayer->getMove(this->board);
			
			if (validMove(this->board, boardAfterPlayerMove, this->currentPlayer->getPlayerBoardValue()))
			{
				this->board = createCopyOfBoard(boardAfterPlayerMove);
				toggleCurrentPlayer();
				if (this->gameSettings.gameType == GameType::Single)
				{
					Sleep(this->gameSettings.delayBetweenMoves);
					printBoard(board);
				}
			}
			else
			{
				std::cout << "Player " << this->currentPlayer->getPlayerBoardValue() << " did not submit a valid move.";
				exit(0);
			}
		}
		
		if(playerHasWon(this->board, this->playerOne->getPlayerBoardValue())) return GameResult::PlayerOneWin;
		else if (playerHasWon(this->board, this->playerTwo->getPlayerBoardValue())) return GameResult::PlayerTwoWin;
		else return GameResult::Tie;
	}
	
	void resetBoard()
	{
		this->board = createEmptyBoard();
	}
	
	void displayStatistics()
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
