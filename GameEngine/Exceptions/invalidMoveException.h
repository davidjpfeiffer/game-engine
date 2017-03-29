#ifndef __INVALIDMOVEEXCEPTION
#define __INVALIDMOVEEXCEPTION

#include <exception>
#include <string>

#include "player.h"

class InvalidMoveException : public std::exception
{
  public:
  
  InvalidMoveException(Player * p_player)
  {
    this->player = p_player;
  }
  
  virtual const char * what() const throw()
  {
    std::string message = this->player->getPlayerValueAsString() + " did not submit a valid move.";
    
    return message.c_str();
  }
  
  private:
  
  Player * player;
};

#endif