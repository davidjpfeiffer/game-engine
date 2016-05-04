#ifndef __GAME
#define __GAME

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "utilities.h"
#include "player.h"

struct GameSettings
{
	bool printEachStep;
};

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
	
	void play(unsigned numberOfGames)
	{
		if(numberOfGames == 1)
		{
			settings.printEachStep = true;
			playWithGraphics();
		}
		else if (numberOfGames > 1)
		{
			settings.printEachStep = false;
			playWithoutGraphics(numberOfGames);
		}
		else std::cout << "Enter a valid number of games to be played.\n";
	}
	
	private:
	
	Player * playerOne;
	Player * playerTwo;
	Player * currentPlayer;
	Board board;
	GameSettings settings;
	
	void playWithGraphics()
	{
		printBoard(board);
		
		GameResult gameResult = getGameResult();
		
		switch(gameResult)
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
	
	GameResult playWithoutGraphics(unsigned numberOfGames)
	{
			GameResult gameResult;
			unsigned playerOneWins = 0, playerTwoWins = 0, tiedGames = 0;
			
			for(int i = 0; i < numberOfGames; i++)
			{
				gameResult = getGameResult();
				
				switch(gameResult)
				{
					case GameResult::PlayerOneWin:
						playerOneWins++;
						break;
					
					case GameResult::PlayerTwoWin:
						playerTwoWins++;
						break;
					
					case GameResult::Tie:
						tiedGames++;
						break;
					
					default:
						std::cout << "An error occured during game execution.\n";
						break;
				}
			}
			
			std::cout << "There were a total of " << numberOfGames << " games played.\n";
			std::cout << "Player One won " << playerOneWins << " games.\n";
			std::cout << "Player Two won " << playerTwoWins << " games.\n";
			std::cout << "There were " << tiedGames << " tied games.\n";	
	}
	
	GameResult getGameResult()
	{
		while(!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
		{
			Board boardAfterPlayerMove = this->currentPlayer->getMove(board);
			
			if (validMove(board, boardAfterPlayerMove, this->currentPlayer->getPlayerBoardValue()))
			{
				board = copyBoard(boardAfterPlayerMove);
				toggleCurrentPlayer();
				if (settings.printEachStep)
				{
					sleep(1);
					printBoard(board);
				}
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