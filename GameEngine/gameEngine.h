#ifndef __GAMEENGINE
#define __GAMEENGINE

#include <iostream>

#include "game.h"
#include "gameResult.h"
#include "player.h"
#include "invalidMoveException.h"

class GameEngine
{
  public:
  
  GameEngine(const Game & game)
  {
    this->gameDefinition = game.gameDefinition;
    this->playerRegistry = game.playerRegistry;
    setNumberOfGames();
    setPlayerOne();
    setPlayerTwo();
    this->currentPlayer = this->playerOne;
    this->gameDefinition->setInitialGameState(& this->gameState);
  }
  
  ~GameEngine()
  {
    delete this->playerOne;
    delete this->playerTwo;
    delete this->gameState;
  }

  void play()
  {
    try
    {
      play_inner();
    }
    catch(std::exception & e)
    {
      std::cout << "-------------------------------\n";
      std::cout << "           Exception           \n";
      std::cout << "-------------------------------\n";
      std::cout << e.what() << '\n';
    }
  }
  
  private:
  
  unsigned numberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
  
  const GameDefinition * gameDefinition;
  const PlayerRegistry * playerRegistry;
  Player * playerOne;
  Player * playerTwo;
  Player * currentPlayer;
  GameState * gameState;

  void play_inner()
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
    
    this->numberOfGames = input;
  }

  bool validNumberOfGames(unsigned p_numberOfGames)
  {
    return p_numberOfGames > 0 && p_numberOfGames <= 10000;
  }
  
  void setPlayerOne()
  {
    std::cout << "-------------------------------\n";
    std::cout << "          Player One           \n";
    std::cout << "-------------------------------\n";
    Player * player = getPlayer();
    player->setPlayerValue(PlayerValue::PlayerOne);
    this->playerOne = player;
    std::cout << "Player One is " << player->getName() << '\n';
  }
  
  void setPlayerTwo()
  {
    std::cout << "-------------------------------\n";
    std::cout << "          Player Two           \n";
    std::cout << "-------------------------------\n";
    Player * player = getPlayer();
    player->setPlayerValue(PlayerValue::PlayerTwo);
    this->playerTwo = player;
    std::cout << "Player Two is " << player->getName() << '\n';
  }
  
  Player * getPlayer() const
  {
    Player * player = nullptr;
    int numberOfPlayers = this->playerRegistry->players.size();
    int choice;
    bool validChoice = false;
    
    while (validChoice == false)
    {
      for (int i = 0; i < numberOfPlayers; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->playerRegistry->players[i]->getName() << '\n';
      }
      
      std::cout << "Choose Player Number: ";
      std::cin >> choice;
      
      if (choice > 0 && choice <= numberOfPlayers)
      {
        player = this->playerRegistry->players[choice - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfPlayers << '\n';
      }
    }
    
    return player;
  }
};

#endif