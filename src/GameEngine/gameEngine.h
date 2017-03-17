#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>

#include "../utilities.h"

#include "game.h"
#include "gameResult.h"
#include "player.h"

class GameEngine
{
  public:
  
  GameEngine(const Game & game)
  {
    setNumberOfGames();
    this->gameDefinition = game.gameDefinition;
    this->playerOne = game.playerRegistry->getPlayerOne();
    this->playerTwo = game.playerRegistry->getPlayerTwo();
    this->currentPlayer = this->playerOne;
    this->gameDefinition->setInitialGameState(& this->gameState);
    
    if (playingSingleGame())
    {
      std::cout << "-------------------------------\n";
    }
  }
  
  ~GameEngine()
  {
    delete this->playerOne;
    delete this->playerTwo;
    delete this->gameState;
  }

  void play()
  {
    for (unsigned gameNumber = 1; gameNumber <= this->numberOfGames; gameNumber++)
    {
      this->gameState->reset();
      
      switch (getGameResult())
      {
        case GameResult::PlayerOneWin:
          if (playingSingleGame())
          {
            std::cout << "Result: " << this->playerOne->getPlayerValueAsString() << " wins!\n";
          }
          else
          {
            this->playerOneWins++;
          }
          break;

        case GameResult::PlayerTwoWin:
          if (playingSingleGame())
          {
            std::cout << "Result: " << this->playerTwo->getPlayerValueAsString() << " wins!\n";
          }
          else
          {
            this->playerTwoWins++;
          }
          break;

        case GameResult::Tie:
          if (playingSingleGame())
          {
            std::cout << "Result: Tie!\n";
          }
          else
          {
            this->gamesTied++;
          }
          break;
      }
    }

    if (playingMultipleGames())
    {
      printResults();
    }
  }
  
  private:
  
  unsigned numberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
  
  const GameDefinition * gameDefinition;
  Player * playerOne;
  Player * playerTwo;
  Player * currentPlayer;
  GameState * gameState;

  GameResult getGameResult()
  {
    if (playingSingleGame())
    {
      this->gameState->print();
    }

    while (gameIsNotOver())
    {
      GameState * gameStateAfterMove = getNextMove();
      
      if (validMove(gameStateAfterMove))
      {
        updateGameState(gameStateAfterMove);
        toggleCurrentPlayer();
        if (playingSingleGame())
        {
          this->gameState->print();
        }
      }
      else
      {
        delete gameStateAfterMove;
        exitWithErrorMessage(this->currentPlayer->getPlayerValueAsString() + " did not submit a valid move.");
      }
    }
    
    if (playerHasWon(PlayerValue::PlayerOne))
    {
      return GameResult::PlayerOneWin;
    }
    else if (playerHasWon(PlayerValue::PlayerTwo))
    {
      return GameResult::PlayerTwoWin;
    }
    else
    {
      return GameResult::Tie;
    }
  }
  
  bool gameIsNotOver()
  {
    return this->gameDefinition->isNotOver(this->gameState);
  }
  
  bool validMove(GameState * gameStateAfterMove)
  {
    return this->gameDefinition->isValidMove(this->gameState, gameStateAfterMove, this->currentPlayer->getPlayerValue());
  }
  
  void updateGameState(GameState * newGameState)
  {
    delete this->gameState;
    this->gameState = newGameState;
  }
  
  bool playerHasWon(PlayerValue playerValue)
  {
    return this->gameDefinition->playerHasWon(this->gameState, playerValue);
  }
  
  GameState * getNextMove()
  {
    GameState * gameStateAfterMove = this->gameState->clone();
    this->currentPlayer->getMove(gameStateAfterMove);
    return gameStateAfterMove;
  }
  
  bool playingSingleGame()
  {
    return this->numberOfGames == 1;
  }

  bool playingMultipleGames()
  {
    return this->numberOfGames > 1;
  }

  void printResults()
  {
    std::cout << "-------------------------------\n";
    std::cout << "            Results            \n";
    std::cout << "-------------------------------\n";
    std::cout << "Player One Wins: " << this->playerOneWins << '\n';
    std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
    std::cout << "Games Tied: " << this->gamesTied << '\n';
    std::cout << "Total Number Of Games: " << this->numberOfGames << '\n';
    std::cout << "-------------------------------\n";
  }

  void toggleCurrentPlayer()
  {
    this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
  }

  void setNumberOfGames()
  {
    std::cout << "-------------------------------\n";
    std::cout << "        Number Of Games        \n";
    std::cout << "-------------------------------\n";
    
    unsigned numberOfGames;
    
    while(!validNumberOfGames(numberOfGames))
    {
      std::cout << "Number of games to play: ";
      std::cin >> numberOfGames;
      
      if (!validNumberOfGames(numberOfGames))
      {
        std::cout << "Invalid entry, number must be between 1 and 10,000 inclusive.";
      }
    }
    
    this->numberOfGames = numberOfGames;
  }

  bool validNumberOfGames(unsigned numberOfGames)
  {
    return numberOfGames > 0 && numberOfGames < 10000;
  }
};

#endif