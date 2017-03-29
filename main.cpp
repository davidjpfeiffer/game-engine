#include <cstdlib>
#include <time.h>

#include "./GameEngine/gameEngine.h"
#include "./Games/ConnectFour/connectFourGame.h"

using namespace std;

int main()
{
  ConnectFourGame game;
  GameEngine gameEngine(game);
  gameEngine.play();
}