#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include <cstdlib>
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
  }

  void play(unsigned numberOfGames)
  {
    this->setNumberOfGames(numberOfGames);

    for (unsigned gameNumber = 1; gameNumber <= this->numberOfGames; gameNumber++)
    {
      resetBoard();

      switch (getGameResult())
      {
      case GameResult::PlayerOneWin:
        if (playingSingleGame()) std::cout << "Result Of game " << gameNumber << ": " << this->playerOne->getName() << " wins!\n";
        else this->playerOneWins++;
        break;

      case GameResult::PlayerTwoWin:
        if (playingSingleGame()) std::cout << "Result Of game " << gameNumber << ": " << this->playerTwo->getName() << " wins!\n";
        else this->playerTwoWins++;
        break;

      case GameResult::Tie:
        if (playingSingleGame()) std::cout << "Result Of game " << gameNumber << ": Tie!\n";
        else this->gamesTied++;
        break;
      }
    }

    if (playingMultipleGames()) displayStatistics();
  }

private:

  unsigned numberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;

  Player * playerOne;
  Player * playerTwo;
  Player * currentPlayer;
  Board board;

  GameResult getGameResult()
  {
    if (playingSingleGame()) printBoard(this->board);

    while (!boardIsInWinningState(this->board) && numAvailableMoves(this->board) > 0)
    {
      Board boardAfterPlayerMove = this->currentPlayer->getMove(this->board);

      if (validMove(this->board, boardAfterPlayerMove, this->currentPlayer->getPlayerBoardValue()))
      {
        this->board = createCopyOfBoard(boardAfterPlayerMove);
        toggleCurrentPlayer();
        if (playingSingleGame())
        {
          printBoard(board);
        }
      }
      else exitWithErrorMessage(this->currentPlayer->getName() + " did not submit a valid move.");
    }

    if (playerHasWon(this->board, this->playerOne->getPlayerBoardValue())) return GameResult::PlayerOneWin;
    else if (playerHasWon(this->board, this->playerTwo->getPlayerBoardValue())) return GameResult::PlayerTwoWin;
    else return GameResult::Tie;
  }

  bool playingSingleGame()
  {
    return this->numberOfGames == 1;
  }

  bool playingMultipleGames()
  {
    return this->numberOfGames > 1;
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
    std::cout << "Total Number Of Games: " << this->numberOfGames << '\n';
    std::cout << "------------------------------\n";
  }

  void toggleCurrentPlayer()
  {
    this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
  }

  void setNumberOfGames(unsigned numberOfGames)
  {
    if (validNumberOfGames(numberOfGames)) this->numberOfGames = numberOfGames;
    else exitWithErrorMessage("Number of games must be greater than 0.");
  }

  bool validNumberOfGames(int numberOfGames)
  {
    return numberOfGames > 0 && numberOfGames < 1000000;
  }
};

#endif