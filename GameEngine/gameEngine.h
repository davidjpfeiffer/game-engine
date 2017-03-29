#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>

#include "./Exceptions/invalidMoveException.h"
#include "./Exceptions/emptyGameRegistryException.h"
#include "./Exceptions/emptyPlayerRegistryException.h"
#include "./Utilities/printer.h"

#include "game.h"
#include "gameRegistry.h"
#include "gameResult.h"
#include "player.h"

class GameEngine
{
  public:
  
  ~GameEngine()
  {
    deleteAllocatedMemory();
  }
  
  void play()
  {
    try
    {
      selectGame();
      selectNumberOfGames();
      selectPlayerOne();
      selectPlayerTwo();
      
      play_inner();
    }
    catch(std::exception & e)
    {
      printer.printHeader("Exception");
      std::cout << e.what() << '\n';
    }
  }
  
  private:
  
  unsigned numberOfGamesToPlay, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
  
  GameRegistry gameRegistry;
  Game * currentGame = nullptr;
  GameState * gameState = nullptr;
  Player * playerOne = nullptr;
  Player * playerTwo = nullptr;
  Player * currentPlayer;
  
  void play_inner()
  {
    for (unsigned gameNumber = 1; gameNumber <= this->numberOfGamesToPlay; gameNumber++)
    {
      this->currentPlayer = this->playerOne;
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
  
  GameResult getGameResult()
  {
    if (playingSingleGame())
    {
      this->gameState->print();
    }

    while (!gameIsOver())
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
        throw InvalidMoveException(this->currentPlayer);
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
  
  bool gameIsOver()
  {
    return this->currentGame->gameDefinition->isOver(this->gameState);
  }
  
  bool validMove(GameState * gameStateAfterMove)
  {
    return this->currentGame->gameDefinition->isValidMove(this->gameState, gameStateAfterMove, this->currentPlayer->getPlayerValue());
  }
  
  void updateGameState(GameState * newGameState)
  {
    delete this->gameState;
    this->gameState = newGameState;
  }
  
  bool playerHasWon(PlayerValue playerValue)
  {
    return this->currentGame->gameDefinition->playerHasWon(this->gameState, playerValue);
  }
  
  GameState * getNextMove()
  {
    GameState * gameStateAfterMove = this->gameState->clone();
    this->currentPlayer->getMove(gameStateAfterMove);
    return gameStateAfterMove;
  }
  
  bool playingSingleGame()
  {
    return this->numberOfGamesToPlay == 1;
  }

  bool playingMultipleGames()
  {
    return this->numberOfGamesToPlay > 1;
  }

  void printResults()
  {
    printer.printHeader("Results");
    std::cout << "Player One Wins: " << this->playerOneWins << '\n';
    std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
    std::cout << "Games Tied: " << this->gamesTied << '\n';
    std::cout << "Total Number Of Games: " << this->numberOfGamesToPlay << '\n';
  }

  void toggleCurrentPlayer()
  {
    this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
  }

  void selectNumberOfGames()
  {
    printer.printHeader("Select Number Of Games");
    
    unsigned input = 0;
    
    do
    {
      std::cout << "Number of games to play: ";
      std::cin >> input;
      
      if (!validNumberOfGames(input))
      {
        std::cout << "Invalid entry, number must be between 1 and 10,000 inclusive.\n";
      }
    }
    while(!validNumberOfGames(input));
    
    this->numberOfGamesToPlay = input;
  }

  bool validNumberOfGames(unsigned p_numberOfGames)
  {
    return p_numberOfGames > 0 && p_numberOfGames <= 10000;
  }
  
  void selectGame()
  {
    if (this->gameRegistry.games.size() == 0)
    {
      throw EmptyGameRegistryException();
    }
    
    printer.printHeader("Select Game");
    this->currentGame = getGame();
    this->currentGame->gameDefinition->setInitialGameState(& this->gameState);
    std::cout << "Game is " << this->currentGame->getName() << '\n';
  }
  
  Game * getGame()
  {
    Game * game = nullptr;
    unsigned choice;
    unsigned numberOfGames = this->gameRegistry.games.size();
    bool validChoice = false;
    while (validChoice == false)
    {
      for(unsigned i = 0; i < numberOfGames; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->gameRegistry.games[i]->getName() << '\n';
      }
      
      std::cout << "Choose Game Number: ";
      std::cin >> choice;
      
      if (choice > 0 && choice <= numberOfGames)
      {
        game = this->gameRegistry.games[choice - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfGames << '\n';
      }
    }
    
    if (game->playerRegistry->players.size() == 0)
    {
      throw EmptyPlayerRegistryException(game);
    }
    
    return game;
  }
  
  void selectPlayerOne()
  {
    printer.printHeader("Select Player One");
    this->playerOne = getPlayer();
    playerOne->setPlayerValue(PlayerValue::PlayerOne);
    std::cout << "Player One is " << playerOne->getName() << '\n';
  }
  
  void selectPlayerTwo()
  {
    printer.printHeader("Select Player Two");
    this->playerTwo = getPlayer();
    playerTwo->setPlayerValue(PlayerValue::PlayerTwo);
    std::cout << "Player Two is " << playerTwo->getName() << '\n';
  }
  
  Player * getPlayer() const
  {
    Player * player = nullptr;
    unsigned numberOfPlayers = this->currentGame->playerRegistry->players.size();
    unsigned choice;
    bool validChoice = false;
    
    while (validChoice == false)
    {
      for (unsigned i = 0; i < numberOfPlayers; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->currentGame->playerRegistry->players[i]->getName() << '\n';
      }
      
      std::cout << "Choose Player Number: ";
      std::cin >> choice;
      
      if (choice > 0 && choice <= numberOfPlayers)
      {
        player = this->currentGame->playerRegistry->players[choice - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfPlayers << '\n';
      }
    }
    
    return player;
  }
  
  void deleteAllocatedMemory()
  {
    if (this->currentGame != nullptr)
    {
      delete this->currentGame;
      this->currentGame = nullptr;
    }
    
    if (this->gameState != nullptr)
    {
      delete this->gameState;
      this->gameState = nullptr;
    }
    
    if (this->playerOne != nullptr)
    {
      delete this->playerOne;
      this->playerOne = nullptr;
    }
    
    if (this->playerTwo != nullptr)
    {
      delete this->playerTwo;
      this->playerTwo = nullptr;
    }
  }
};

#endif