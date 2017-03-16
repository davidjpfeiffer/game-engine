#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include "game.h"
#include "player.h"
#include "ticTacToe.h"

class GameEngine
{
  public:
  
  GameEngine(Game & game, Player & playerOne, Player & playerTwo)
  {
    this->game = & game;
    this->playerOne = & playerOne;
    this->playerTwo = & playerTwo;
    this->currentPlayer = this->playerOne;
    
    this->game->setupPlayers(playerOne, playerTwo);
    this->game->createGameState(& this->gameState);
  }
  
  ~GameEngine()
  {
    this->game->deleteGameState(& this->gameState);
  }

  void play(unsigned numberOfGames = 1)
  {
    this->setNumberOfGames(numberOfGames);

    for (unsigned gameNumber = 1; gameNumber <= this->numberOfGames; gameNumber++)
    {
      this->gameState->reset();
      
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

    if (playingMultipleGames()) displayResults();
  }
  
  private:
  
  unsigned numberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
  
  Game * game;
  Player * playerOne;
  Player * playerTwo;
  Player * currentPlayer;
  GameState * gameState;

  GameResult getGameResult()
  {
    if (playingSingleGame()) this->gameState->print();

    while (!this->game->isOver(this->gameState))
    {
      GameState * gameStateAfterMove = this->game->getCopyOfGameState(this->gameState);
      this->currentPlayer->getMove(gameStateAfterMove);
      
      if (this->game->isValidMove(this->gameState, gameStateAfterMove, this->currentPlayer->getPlayerValue()))
      {
        delete this->gameState;
        this->gameState = gameStateAfterMove;
        
        toggleCurrentPlayer();
        if (playingSingleGame()) this->gameState->print();
      }
      else
      {
        delete gameStateAfterMove;
        
        exitWithErrorMessage(this->currentPlayer->getName() + " did not submit a valid move.");
      }
    }
    
    if (this->game->playerHasWon(this->gameState, PlayerValue::PlayerOne)) return GameResult::PlayerOneWin;
    else if (this->game->playerHasWon(this->gameState, PlayerValue::PlayerTwo)) return GameResult::PlayerTwoWin;
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

  void displayResults()
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
    return numberOfGames < 10000;
  }
};

#endif