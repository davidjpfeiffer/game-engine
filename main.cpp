#include <cstdlib>

#include "game.h"

#include "randomPlayer.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

using namespace std;

int main(int argc, char** argv)
{
	HumanPlayer playerOne;
	ComputerPlayer playerTwo;
	
	Game game(playerOne, playerTwo);
	game.play(argc == 2 ? atoi(argv[1]) : 1);
}