#ifndef __PLAYERREGISTRY
#define __PLAYERREGISTRY

#include <iostream>
#include <vector>
#include <string>

#include "player.h"

class PlayerRegistry
{
  public:
  
  Player * getPlayerOne() const
  {
    printHeader("Player One");
    Player * player = getPlayer();
    player->setPlayerValue(PlayerValue::PlayerOne);
    std::cout << "Player One is " << player->getName() << '\n';
    return player;
  }
  
  Player * getPlayerTwo() const
  {
    printHeader("Player Two");
    Player * player = getPlayer();
    player->setPlayerValue(PlayerValue::PlayerTwo);
    std::cout << "Player Two is " << player->getName() << '\n';
    return player;
  }
  
  protected:
  
  std::vector<Player *> players;
  
  private:
  
  Player * getPlayer() const
  {
    Player * player = nullptr;
    int numberOfPlayers = this->players.size();
    int choice;
    bool validChoice = false;
    
    while (validChoice == false)
    {
      for (int i = 0; i < numberOfPlayers; i++)
      {
        std::cout << "Choice " << i + 1 << ": " << this->players[i]->getName() << '\n';
      }
      
      std::cout << "Choose Player Number: ";
      std::cin >> choice;
      
      if (choice > 0 && choice <= numberOfPlayers)
      {
        player = this->players[choice - 1]->clone();
        validChoice = true;
      }
      else
      {
        std::cout << "Invalid choice, please enter a number from 1 to " << numberOfPlayers << '\n';
      }
    }
    
    return player;
  }
  
  void printHeader(std::string player) const
  {
    std::cout << "-------------------------------\n";
    std::cout << "          " << player << "           \n";
    std::cout << "-------------------------------\n";
  }
};

#endif