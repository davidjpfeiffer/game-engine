#include <cstdlib>
#include <time.h>

#include "gameEngine.h"

#include "ticTacToe.h"

#include "randomTicTacToePlayer.h"
#include "humanTicTacToePlayer.h"
#include "computerTicTacToePlayer.h"

using namespace std;

int main()
{
  srand(time(NULL));

  TicTacToe game;
  RandomTicTacToePlayer playerOne;
  RandomTicTacToePlayer playerTwo;
  
  GameEngine gameEngine(game, playerOne, playerTwo);
  gameEngine.play();
}