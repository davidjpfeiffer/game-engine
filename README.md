## Game Engine for Tic Tac Toe

This project was originally written for Tic Tac Toe, but is currently being redesigned to work for any two-player turn-based strategy game. This process should be completed before Summer 2017. All documentation for this project will be updated after redesign.

This simple C++ command line interface program written by David Pfeiffer for the 2016 Southeast Missouri State Hackathon allows any two algorithms to face off in a game of Tic Tac Toe. The program was written to better understand how game engines work. In the future I plan to make game engines that work for more complex games like Connect Four or chess.

### Project Setup

Open a command line prompt in the directory you would like to clone the project. You can clone, compile, and run the project using the following commands:
```
$ git clone https://github.com/davidjpfeiffer/tic-tac-toe
$ cd tic-tac-toe/src
$ g++ -o main -std=c++11 main.cpp
$ main.exe
```

### Getting Started

To create and play games you must include the game engine and a collection of algorithms (called players) into a program. The `Game` constructor accepts two arguments of type `Player`. Once a game is created, you can execute the game by calling the `play()` method on the game object.

```c++
int main()
{
	HumanPlayer playerOne;
	ComputerPlayer playerTwo;
	
	Game game(playerOne, playerTwo);
	game.play();
}
```

### Pre-Built Algorithms

* Random Player
 * Selects a random move every turn
 * Should be default move for all other algorithms
* Computer Player
 * A simple algorithm that makes moves based on certain conditions
 * Because this game is easy, this algorithm actually plays a perfect game
* Human Player
 * Prompts the user to enter input for each move
 * Works just like other algorithms
 * Allows humans to play computers, and other fun combinations

### Create Your Own Algorithm

Tic Tac Toe is an easy game, so the algorithms aren't hard to write. If you would like to create your own for fun, create a C++ class that inherits from the abstract base class `Player`. You must implement the `getMove()` method on your new class, which the game engine will use to get your move each turn. The current game board will be passed to you as a parameter, and you must return a new game board with your desired move. The game engine checks to make sure that all moves made are valid.

You can determine which player you are using the `getBoardValue()` method implemented on the Player class. This returns a `BoardValue` which is an enumeration defined in <i>utilities.cpp</i>. Your opponents board value is also available.

```c++
class MyPlayer : public Player
{
	public:
	
	Board getMove(const Board & board)
	{
		Board newBoard = board;
		
		// Make changes to newBoard
		
		return newBoard;
	}
};
```
