#ifndef __GAMERESULTS
#define __GAMERESULTS

#include <iostream>

#include "./Utilities/printer.h"
#include "./Exceptions/totalNumberOfGamesNotSetException.h"

#include "gameResult.h"

class GameResults
{
  public:
  
  void print(unsigned totalNumberOfGames) const
  {
    printer.printHeader("Results");
    std::cout << "Player One Wins: " << this->playerOneWins << '\n';
    std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
    std::cout << "Number of Games Tied: " << this->gamesTied << '\n';
    std::cout << "Total Number of Games: " << totalNumberOfGames << '\n';
  }
  
  void logPlayerOneWin()
  {
    this->playerOneWins++;
  }
  
  void logPlayerTwoWin()
  {
    this->playerTwoWins++;
  }
  
  void logTieGame()
  {
    this->gamesTied++;
  }
  
  void reset()
  {
    this->playerOneWins = 0;
    this->playerTwoWins = 0;
    this->gamesTied = 0;
  }
  
  private:
  
  unsigned playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
};

#endif