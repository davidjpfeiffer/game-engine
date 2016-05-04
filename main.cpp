#include <cstdlib>
#include <time.h>

#include "game.h"

#include "randomPlayer.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

using namespace std;

int main()
{
	srand(time(NULL));
	
	RandomPlayer playerOne;
	RandomPlayer playerTwo;
	
	Game game(playerOne, playerTwo);
	game.play();
}