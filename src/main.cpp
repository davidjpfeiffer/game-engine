#include <cstdlib>
#include <time.h>

#include "./GameEngine/gameEngine.h"
#include "./TicTacToe/ticTacToeGame.h"

using namespace std;

int main()
{
  srand(time(NULL));
  
  TicTacToeGame game;
  GameEngine gameEngine(game);
  gameEngine.play();
}