#include <cstdlib>
#include <time.h>

#include "./GameEngine/gameEngine.h"
#include "./Games/TicTacToe/ticTacToeGame.h"
#include "./Games/ConnectFour/connectFourGame.h"

using namespace std;

int main()
{
  TicTacToeGame ticTacToe;
  ConnectFourGame connectFour;
  GameEngine gameEngine(connectFour);
  gameEngine.play();
}