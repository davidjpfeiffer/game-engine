#ifndef __INVALIDMOVEEXCEPTION
#define __INVALIDMOVEEXCEPTION

#include <exception>
#include <string>
#include <cstring>

#include "../player.h"

class InvalidMoveException : public std::exception
{
  public:
  
  InvalidMoveException(Player * p_player)
  {
    std::string message = p_player->getPlayerValueAsString() + " did not submit a valid move.";
    cstr_message = new char [message.length() + 1];
    std::strcpy(cstr_message, message.c_str());
  }
  
  ~InvalidMoveException()
  {
    delete [] cstr_message;
  }
  
  virtual const char * what() const throw()
  {
    return cstr_message;
  }
  
  private:
  
  char * cstr_message;
};

#endif