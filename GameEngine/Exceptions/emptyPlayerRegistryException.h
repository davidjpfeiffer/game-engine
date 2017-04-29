#ifndef __EMPTYPLAYERREGISTRYEXCEPTION
#define __EMPTYPLAYERREGISTRYEXCEPTION

#include <exception>
#include <string>
#include <cstring>

#include "../game.h"

class EmptyPlayerRegistryException : public std::exception
{
  public:
  
  EmptyPlayerRegistryException(Game * p_game)
  {
    std::string message = "No players have been registered with the " + p_game->getName() + " game.";
    cstr_message = new char [message.length() + 1];
    std::strcpy(cstr_message, message.c_str());
  }
  
  ~EmptyPlayerRegistryException()
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