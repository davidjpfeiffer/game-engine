#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>
#include <omp.h>

#include "./Exceptions/invalidMoveException.h"
#include "./Exceptions/emptyGameRegistryException.h"
#include "./Exceptions/emptyPlayerRegistryException.h"
#include "./Utilities/printer.h"

#include "game.h"
#include "gameRegistry.h"
#include "gameResult.h"
#include "gameResults.h"
#include "player.h"

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
      if (!gameSelected()) selectGame();
      if (!numberOfGamesSelected()) selectNumberOfGames();
      if (!playerOneSelected()) selectPlayerOne();
      if (!playerTwoSelected()) selectPlayerTwo();
      
      play();
    }
    catch(std::exception & e)
    {
      printer.printHeader("Exception");
      std::cout << e.what() << '\n';
    }
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
  }
  
  void selectNumberOfGames()
  {
    printer.printHeader("Select Number Of Games");
    
    unsigned numberOfGames = 0;
    
    do
    {
      std::cout << "Number of games to play: ";
      std::cin >> numberOfGames;
      
      if (!validNumberOfGamesToPlay(numberOfGames))
      {
        std::cout << "Invalid entry, number must be between 1 and 100,000 inclusive.\n";
      }
    }
    while(!validNumberOfGamesToPlay(numberOfGames));
    
    this->totalNumberOfGames = numberOfGames;
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
  
  private:
  
  unsigned totalNumberOfGames = 0;
  
  GameRegistry gameRegistry;
  GameResults gameResults;
  
  Game * game = nullptr;
  Player * playerOne = nullptr;
  Player * playerTwo = nullptr;
  
  void play()
  {
    #pragma omp parallel for
    for (unsigned gameNumber = 1; gameNumber <= this->totalNumberOfGames; gameNumber++)
    {
      switch (getGameResult())
      {
        case GameResult::PlayerOneWin:
          #pragma omp critical
          this->gameResults.logPlayerOneWin();
          break;

        case GameResult::PlayerTwoWin:
          #pragma omp critical
          this->gameResults.logPlayerTwoWin();
          break;

        case GameResult::Tie:
          #pragma omp critical
          this->gameResults.logTieGame();
          break;
      }
    }

    if (playingMultipleGames())
    {
      this->gameResults.print();
    }
  }
  
  GameResult getGameResult()
  {
    GameState * gameState = this->game->gameDefinition->getInitialGameState();
    Player * currentPlayer = this->playerOne;
    
    if (playingSingleGame())
    {
      gameState->print();
    }
    
    while (!gameIsOver(gameState))
    {
      GameState * gameStateAfterMove = getNextMove(gameState, currentPlayer);
      if (isValidMove(gameState, gameStateAfterMove, currentPlayer))
      {
        delete gameState;
        gameState = gameStateAfterMove;
        toggleCurrentPlayer(&currentPlayer);
        
        if (playingSingleGame())
        {
          gameState->print();
        }
      }
      else
      {
        delete gameState;
        delete gameStateAfterMove;
        throw InvalidMoveException(currentPlayer);
      }
    }

    delete gameState;
    
    if (playerHasWon(gameState, PlayerValue::PlayerOne))
    {
      if (playingSingleGame())
      {
        std::cout << "Result: " << this->playerOne->getPlayerValueAsString() << " wins!\n";
      }
      
      return GameResult::PlayerOneWin;
    }
    else if (playerHasWon(gameState, PlayerValue::PlayerTwo))
    {
      if (playingSingleGame())
      {
        std::cout << "Result: " << this->playerTwo->getPlayerValueAsString() << " wins!\n";
      }
      
      return GameResult::PlayerTwoWin;
    }
    else
    {
      if (playingSingleGame())
      {
        std::cout << "Result: Tie!\n";
      }
      
      return GameResult::Tie;
    }
  }
  
  bool gameIsOver(GameState * gameState)
  {
    return this->game->gameDefinition->isOver(gameState);
  }
  
  bool isValidMove(GameState * gameStateBeforeMove, GameState * gameStateAfterMove, Player * currentPlayer)
  {
    return this->game->gameDefinition->isValidMove(gameStateBeforeMove, gameStateAfterMove, currentPlayer->getPlayerValue());
  }
  
  bool playerHasWon(GameState * gameState, PlayerValue playerValue)
  {
    return this->game->gameDefinition->playerHasWon(gameState, playerValue);
  }
  
  GameState * getNextMove(GameState * gameState, Player * currentPlayer)
  {
    GameState * gameStateAfterMove = gameState->clone();
    currentPlayer->getMove(gameStateAfterMove);
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

  bool validNumberOfGamesToPlay(unsigned numberOfGames)
  {
    return numberOfGames > 0 && numberOfGames <= 100000;
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
  
  bool gameSelected()
  {
    return this->game != nullptr;
  }
  
  bool numberOfGamesSelected()
  {
    return this->totalNumberOfGames != 0;
  }
  
  bool playerOneSelected()
  {
    return this->playerOne != nullptr;
  }
  
  bool playerTwoSelected()
  {
    return this->playerTwo != nullptr;
  }
  
  void toggleCurrentPlayer(Player ** currentPlayer)
  {
    *currentPlayer = *currentPlayer == this->playerOne ? this->playerTwo : this->playerOne;
  }
  
  void deleteAllocatedMemory()
  {
    if (this->game != nullptr)
    {
      delete this->game;
      this->game = nullptr;
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