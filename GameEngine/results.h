#ifndef __RESULTS
#define __RESULTS

#include <iostream>

#include "./Utilities/printer.h"

class Results
{
  public:
  
  void print() const
  {
    if (this->totalNumberOfGamesSet)
    {
      printer.printHeader("Results");
      std::cout << "Player One Wins: " << this->playerOneWins << '\n';
      std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
      std::cout << "Number of Games Tied: " << this->gamesTied << '\n';
      std::cout << "Total Number of Games: " << this->totalNumberOfGames << '\n';
    }
    else
    {
      std::cout << "Total number of games has not been set.\n";
    }
  }
  
  void setTotalNumberOfGames(unsigned p_totalNumberOfGames)
  {
    this->totalNumberOfGames = p_totalNumberOfGames;
    this->totalNumberOfGamesSet = true;
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
    this->totalNumberOfGames = 0;
    this->totalNumberOfGamesSet = false;
  }
  
  private:
  
  bool totalNumberOfGamesSet = false;
  unsigned totalNumberOfGames, playerOneWins = 0, playerTwoWins = 0, gamesTied = 0;
};

#endif