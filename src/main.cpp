#include <cstdlib>
#include <time.h>

#include "gameEngine.h"
#include "ticTacToeGame.h"

using namespace std;

int main()
{
  srand(time(NULL));
  
  TicTacToeGame game;
  GameEngine gameEngine(game);
  gameEngine.play();
}