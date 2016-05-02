#include "utilities.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#ifndef __GAME
#define __GAME

class Game
{
	private:
	
	Player * playerOne;
	Player * playerTwo;
	IBoard board;
	
	public:
	
	Game(Player & playerOne, Player & playerTwo)
	{
		playerOne.setPlayerBoardValue(BoardValue::O);
		playerTwo.setPlayerBoardValue(BoardValue::X);
		
		this->playerOne = &playerOne;
		this->playerTwo = &playerTwo;
		this->board = createNewBoard();
	}
	
	void play(unsigned numberOfGames)
	{
		if(numberOfGames == 1) playWithGraphics();
		else if (numberOfGames > 1) playWithoutGraphics(numberOfGames);
		else std::cout << "Enter a valid number of games to be played.\n";
	}
	
	void playWithGraphics()
	{
		printBoard(board);
		
		while(!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
		{	
			IBoard boardAfterPlayerOneMove = playerOne->getMove(board);
			
			if (validMove(board, boardAfterPlayerOneMove, playerOne->getPlayerBoardValue()))
			{
				board = copyBoard(boardAfterPlayerOneMove);
				sleep(1);
				printBoard(board);
			}
			else
			{
				std::cout << "Player one did not submit a valid move.";
				exit(0);
			}
			
			if (!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
			{
				IBoard boardAfterPlayerTwoMove = playerTwo->getMove(board);
				
				if (validMove(board, boardAfterPlayerTwoMove, playerTwo->getPlayerBoardValue()))
				{
					board = copyBoard(boardAfterPlayerTwoMove);
					sleep(1);
					printBoard(board);
				}
				else
				{
					std::cout << "Player two did not submit a valid move.\n";
					exit(0);
				}
			}
		}
		
		if(playerHasWon(board, playerOne->getPlayerBoardValue())) std::cout << "Result Of game: Player One Wins!\n";
		else if (playerHasWon(board, playerTwo->getPlayerBoardValue())) std::cout << "Result Of game: Player Two Wins!\n";
		else std::cout << "Result Of Game: Tie!\n";
	}
	
	GameResult playWithoutGraphics(unsigned numberOfGames)
	{
			GameResult result;
			unsigned playerOneWins = 0, playerTwoWins = 0, tiedGames = 0;
			
			for(int i = 0; i < numberOfGames; i++)
			{
				result = getGameResult();
				
				switch(result)
				{
					case PlayerOneWin:
						playerOneWins++;
						break;
					
					case PlayerTwoWin:
						playerTwoWins++;
						break;
					
					case Tie:
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
			IBoard boardAfterPlayerOneMove = playerOne->getMove(board);
			
			if (validMove(board, boardAfterPlayerOneMove, playerOne->getPlayerBoardValue()))
			{
				board = copyBoard(boardAfterPlayerOneMove);
			}
			else
			{
				std::cout << "Player one did not submit a valid move.";
				exit(0);
			}
			
			if (!boardIsInWinningState(board) && numAvailableMoves(board) > 0)
			{
				IBoard boardAfterPlayerTwoMove = playerTwo->getMove(board);
				
				if (validMove(board, boardAfterPlayerTwoMove, playerTwo->getPlayerBoardValue()))
				{
					board = copyBoard(boardAfterPlayerTwoMove);
				}
				else
				{
					std::cout << "Player two did not submit a valid move.\n";
					exit(0);
				}
			}
		}
		
		if(playerHasWon(board, playerOne->getPlayerBoardValue())) return PlayerOneWin;
		else if (playerHasWon(board, playerTwo->getPlayerBoardValue())) return PlayerTwoWin;
		else return Tie;
	}
};

#endif