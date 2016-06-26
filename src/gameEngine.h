#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "utilities.h"
#include "player.h"

class GameEngine
{
	public:
	
	GameEngine(Player & playerOne, Player & playerTwo)
	{
		playerOne.setPlayerBoardValue(BoardValue::PlayerOne);
		playerTwo.setPlayerBoardValue(BoardValue::PlayerTwo);

		this->playerOne = & playerOne;
		this->playerTwo = & playerTwo;
		this->currentPlayer = this->playerOne;
		
		this->gameSettings.gameType = GameType::Single;
		this->gameSettings.numberOfGames = 1;
	}
	
	void play(unsigned numberOfGames)
	{
		this->configureGameSettings(numberOfGames);
		
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
	
	struct GameSettings
	{
		GameType gameType;
		unsigned numberOfGames;
	} gameSettings;
	
	unsigned playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	
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
	
	void toggleCurrentPlayer()
	{
		this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
	}
	
	void configureGameSettings(unsigned numberOfGames)
	{
		if (numberOfGames == 1)
		{
			this->gameSettings.gameType = GameType::Single;
		}
		else
		{
			this->gameSettings.gameType = GameType::Multiple;
		}
		
		this->gameSettings.numberOfGames = numberOfGames;
	}
};

#endif