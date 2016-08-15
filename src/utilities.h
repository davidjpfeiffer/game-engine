#ifndef __UTILITIES
#define __UTILITIES

#include <iostream>
#include <utility>
#include <string>

unsigned getRandomNumber(unsigned mod)
{
  if (mod == 0)
  {
    return 0;
  }
  else
  {
    return rand() % mod;
  }
}

void exitWithErrorMessage(std::string errorMessage)
{
  std::cout << errorMessage << '\n';
  exit(1);
}

#endif