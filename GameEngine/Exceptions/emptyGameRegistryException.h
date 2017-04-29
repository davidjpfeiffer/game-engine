#ifndef __EMPTYGAMEREGISTRYEXCEPTION
#define __EMPTYGAMEREGISTRYEXCEPTION

#include <exception>

class EmptyGameRegistryException : public std::exception
{
  public:
  
  EmptyGameRegistryException()
  {
  }
  
  virtual const char * what() const throw()
  {
    return "No games have been registered with the game registry.";
  }
};

#endif