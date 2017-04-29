#ifndef __GAMERESULTS
#define __GAMERESULTS

#include <iostream>

#include "./Utilities/printer.h"

#include "gameResult.h"

class GameResults
{
  public:
  
  void print() const
  {
    printer.printHeader("Results");
    std::cout << "Player One Wins: " << this->playerOneWins << '\n';
    std::cout << "Player Two Wins: " << this->playerTwoWins << '\n';
    std::cout << "Number of Games Tied: " << this->gamesTied << '\n';
    std::cout << "Total Number of Games: " << this->totalNumberOfGames << '\n';
  }
  
  void logPlayerOneWin()
  {
    this->playerOneWins++;
	this->totalNumberOfGames++;
  }
  
  void logPlayerTwoWin()
  {
    this->playerTwoWins++;
	this->totalNumberOfGames++;
  }
  
  void logTieGame()
  {
    this->gamesTied++;
	this->totalNumberOfGames++;
  }
  
  void reset()
  {
    this->playerOneWins = 0;
    this->playerTwoWins = 0;
    this->gamesTied = 0;
	this->totalNumberOfGames = 0;
  }
  
  private:
  
  unsigned playerOneWins = 0, playerTwoWins = 0, gamesTied = 0, totalNumberOfGames = 0;
};

#endif