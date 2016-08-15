#include <cstdlib>
#include <time.h>

#include "gameEngine.h"
#include "randomPlayer.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

using namespace std;

int main()
{
  srand(time(NULL));

  RandomPlayer playerOne;
  RandomPlayer playerTwo;

  GameEngine gameEngine(playerOne, playerTwo);
  gameEngine.play();
}