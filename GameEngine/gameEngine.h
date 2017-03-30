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
#include "results.h"

class GameEngine
{
  public:
  
  ~GameEngine()
  {
    deleteAllocatedMemory();
  }
  
  void start()
  {
    try
    {
      selectGame();
      selectNumberOfGamesToPlay();
      selectPlayerOne();
      selectPlayerTwo();
      
      play();
    }
    catch(std::exception & e)
    {
      printer.printHeader("Exception");
      std::cout << e.what() << '\n';
    }
  }
  
  private:
  
  Results results;
  unsigned totalNumberOfGames;
  
  GameRegistry gameRegistry;
  Game * game = nullptr;
  GameState * gameState = nullptr;
  Player * playerOne = nullptr;
  Player * playerTwo = nullptr;
  Player * currentPlayer;
  
  void play()
  {
    for (unsigned gameNumber = 1; gameNumber <= this->totalNumberOfGames; gameNumber++)
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
            this->results.logPlayerOneWin();
          }
          break;

        case GameResult::PlayerTwoWin:
          if (playingSingleGame())
          {
            std::cout << "Result: " << this->playerTwo->getPlayerValueAsString() << " wins!\n";
          }
          else
          {
            this->results.logPlayerTwoWin();
          }
          break;

        case GameResult::Tie:
          if (playingSingleGame())
          {
            std::cout << "Result: Tie!\n";
          }
          else
          {
            this->results.logTieGame();
          }
          break;
      }
    }

    if (playingMultipleGames())
    {
      this->results.print();
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
    return this->game->gameDefinition->isOver(this->gameState);
  }
  
  bool validMove(GameState * gameStateAfterMove)
  {
    return this->game->gameDefinition->isValidMove(this->gameState, gameStateAfterMove, this->currentPlayer->getPlayerValue());
  }
  
  void updateGameState(GameState * newGameState)
  {
    delete this->gameState;
    this->gameState = newGameState;
  }
  
  bool playerHasWon(PlayerValue playerValue)
  {
    return this->game->gameDefinition->playerHasWon(this->gameState, playerValue);
  }
  
  GameState * getNextMove()
  {
    GameState * gameStateAfterMove = this->gameState->clone();
    this->currentPlayer->getMove(gameStateAfterMove);
    return gameStateAfterMove;
  }
  
  bool playingSingleGame()
  {
    return this->totalNumberOfGames == 1;
  }

  bool playingMultipleGames()
  {
    return this->totalNumberOfGames > 1;
  }

  void toggleCurrentPlayer()
  {
    this->currentPlayer = this->currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
  }

  void selectNumberOfGamesToPlay()
  {
    printer.printHeader("Select Number Of Games");
    
    unsigned numberOfGames = 0;
    
    do
    {
      std::cout << "Number of games to play: ";
      std::cin >> numberOfGames;
      
      if (!validNumberOfGamesToPlay(numberOfGames))
      {
        std::cout << "Invalid entry, number must be between 1 and 10,000 inclusive.\n";
      }
    }
    while(!validNumberOfGamesToPlay(numberOfGames));
    
    this->totalNumberOfGames = numberOfGames;
    this->results.setTotalNumberOfGames(numberOfGames);
  }

  bool validNumberOfGamesToPlay(unsigned p_numberOfGames)
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
    this->game = getGame();
    std::cout << "test";
    std::cout << "Game is " << this->game->getName() << '\n';
    this->game->gameDefinition->setInitialGameState(& this->gameState);
    
  }
  
  Game * getGame()
  {
    Game * chosenGame = nullptr;
    unsigned chosenGameIndex;
    unsigned numberOfGames = this->gameRegistry.games.size();
    bool validChoice = false;
    
    while (validChoice == false)
    {
      for(unsigned i = 0; i < numberOfGames; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->gameRegistry.games[i]->getName() << '\n';
      }
      
      std::cout << "Choose Game Number: ";
      std::cin >> chosenGameIndex;
      
      if (chosenGameIndex > 0 && chosenGameIndex <= numberOfGames)
      {
        chosenGame = this->gameRegistry.games[chosenGameIndex - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfGames << '\n';
      }
    }
    if (chosenGame->playerRegistry->players.size() == 0)
    {
      throw EmptyPlayerRegistryException(chosenGame);
    }
    
    return chosenGame;
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
    Player * chosenPlayer = nullptr;
    unsigned chosenPlayerIndex;
    unsigned numberOfPlayers = this->game->playerRegistry->players.size();
    bool validChoice = false;
    
    while (validChoice == false)
    {
      for (unsigned i = 0; i < numberOfPlayers; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->game->playerRegistry->players[i]->getName() << '\n';
      }
      
      std::cout << "Choose Player Number: ";
      std::cin >> chosenPlayerIndex;
      
      if (chosenPlayerIndex > 0 && chosenPlayerIndex <= numberOfPlayers)
      {
        chosenPlayer = this->game->playerRegistry->players[chosenPlayerIndex - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfPlayers << '\n';
      }
    }
    
    return chosenPlayer;
  }
  
  void deleteAllocatedMemory()
  {
    if (this->game != nullptr)
    {
      delete this->game;
      this->game = nullptr;
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