#include <cstdlib>
#include <time.h>

#include "gameEngine.h"

#include "ticTacToe.h"
#include "ticTacToePlayerRegistry.h"

#include "randomTicTacToePlayer.h"
#include "humanTicTacToePlayer.h"
#include "computerTicTacToePlayer.h"

using namespace std;

int main()
{
  srand(time(NULL));
  
  TicTacToe game;
  TicTacToePlayerRegistry playerRegistry;
  
  GameEngine gameEngine(game, playerRegistry);
  gameEngine.play();
}