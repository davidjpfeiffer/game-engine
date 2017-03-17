#ifndef __UTILITIES
#define __UTILITIES

#include <iostream>
#include <string>

void exitWithErrorMessage(std::string errorMessage)
{
  std::cout << errorMessage << '\n';
  exit(1);
}

#endif