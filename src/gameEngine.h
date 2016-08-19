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
    playerOne.setBoardValue(BoardValue::PlayerOne); // make this a method on the game object
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
      this->gameState.reset();

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
  GameState gameState;
  TicTacToe game;

  GameResult getGameResult()
  {
    if (isPlayingSingleGame()) this->gameState.print();

    while (!this->game.isOver(this->gameState))
    {
      GameState gameStateAfterMove = this->currentPlayer->getMove(this->gameState);

      if (this->game.isValidMove(this->gameState, gameStateAfterMove, this->currentPlayer->getBoardValue()))
      {
        this->gameState = gameStateAfterMove;
        toggleCurrentPlayer();
        if (isPlayingSingleGame()) this->gameState.print();
      }
      else exitWithErrorMessage(this->currentPlayer->getName() + " did not submit a valid move.");
    }

    if (this->game.playerOneHasWon(this->gameState)) return GameResult::PlayerOneWin;
    else if (this->game.playerTwoHasWon(this->gameState)) return GameResult::PlayerTwoWin;
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
    else exitWithErrorMessage("Number of games must be less than 10,000.");
  }

  bool isValidNumberOfGames(unsigned numberOfGames)
  {
    return numberOfGames < 100000;
  }
};

#endif