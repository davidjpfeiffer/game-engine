#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include "ticTacToe.h"
#include "player.h"

class GameEngine
{
public:

  GameEngine(Player & playerOne, Player & playerTwo)
  {
    playerOne.setBoardValue(BoardValue::PlayerOne);
    playerTwo.setBoardValue(BoardValue::PlayerTwo);

    this->playerOne = & playerOne;
    this->playerTwo = & playerTwo;
    this->currentPlayer = this->playerOne;
  }

  void play(unsigned numberOfGames = 1)
  {
    this->setNumberOfGames(numberOfGames);

    for (unsigned gameNumber = 1; gameNumber <= this->numberOfGames; gameNumber++)
    {
      this->board.reset();

      switch (getGameResult())
      {
      case GameResult::PlayerOneWin:
        if (isPlayingSingleGame()) std::cout << "Result Of game " << gameNumber << ": " << this->playerOne->getName() << " wins!\n";
        else this->playerOneWins++;
        break;

      case GameResult::PlayerTwoWin:
        if (isPlayingSingleGame()) std::cout << "Result Of game " << gameNumber << ": " << this->playerTwo->getName() << " wins!\n";
        else this->playerTwoWins++;
        break;

      case GameResult::Tie:
        if (isPlayingSingleGame()) std::cout << "Result Of game " << gameNumber << ": Tie!\n";
        else this->gamesTied++;
        break;
      }
    }

    if (isPlayingMultipleGames()) displayStatistics();
  }

private:

  unsigned numberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;

  Player * playerOne;
  Player * playerTwo;
  Player * currentPlayer;
  Board board;
  TicTacToe game;

  GameResult getGameResult()
  {
    if (isPlayingSingleGame()) this->board.print();

    while (!this->game.isOver(this->board))
    {
      Board boardAfterMove = this->currentPlayer->getMove(this->board);

      if (this->game.isValidMove(this->board, boardAfterMove, this->currentPlayer->getBoardValue()))
      {
        this->board = boardAfterMove;
        toggleCurrentPlayer();
        if (isPlayingSingleGame()) this->board.print();
      }
      else exitWithErrorMessage(this->currentPlayer->getName() + " did not submit a valid move.");
    }

    if (this->game.playerOneHasWon(this->board)) return GameResult::PlayerOneWin;
    else if (this->game.playerTwoHasWon(this->board)) return GameResult::PlayerTwoWin;
    else return GameResult::Tie;
  }

  bool isPlayingSingleGame()
  {
    return this->numberOfGames == 1;
  }

  bool isPlayingMultipleGames()
  {
    return this->numberOfGames > 1;
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
    if (isValidNumberOfGames(numberOfGames)) this->numberOfGames = numberOfGames;
    else exitWithErrorMessage("Number of games must be greater than 0.");
  }

  bool isValidNumberOfGames(unsigned numberOfGames)
  {
    return numberOfGames > 0 && numberOfGames < 1000000;
  }
};

#endif