#include <cstdlib>
#include <time.h>

#include "gameEngine.h"

#include "ticTacToe.h"

#include "randomPlayer.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

using namespace std;

int main()
{
  srand(time(NULL));

  TicTacToe game;
  RandomPlayer playerOne;
  RandomPlayer playerTwo;

  GameEngine gameEngine(game, playerOne, playerTwo);
  gameEngine.play();
}