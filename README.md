## A C++ Game Engine for Tic Tac Toe

This simple C++ command line interface program written by David Pfeiffer for the 2016 Southeast Missouri State Hackathon allows any two algorithms to face off in a game of Tic Tac Toe. The program was written to better understand how game engines work. In the future I plan to make game engines that work for more complex games like Connect Four or chess.

### Getting Started

To create and play games you must include the game engine and a collection of algorithms (called players) into a program. The <code>Game</code> constructor accepts two arguments of type <code>Player</code>. Once a game is created, you can execute the game by calling the <code>play()</code> method on the game object, which takes the number of games to be played as an argument. An example <i>main.cpp</i> that takes the number of games to be played as a command line argument is included in the project.

```c++
int main()
{
	HumanPlayer playerOne;
	ComputerPlayer playerTwo;
	
	Game game(playerOne, playerTwo);
	game.play(1);
}
```

The result of the game will be output to the console. If the number of games is one, each move will be displayed individually with a one second delay. If the number of games is greater than one, the results will be summarized as a statistic.

### How To Compile

This project was written in C++ 11. You must indicate which version you are using when compiling. This can be done using the following command, which should be run inside the project directory.

```
g++ -o main -std=c++11 main.cpp
```

### Pre-Built Algorithms

<ul>
<li>Random Player</li>
<ul>
<li>Selects a random move every turn</li>
<li>Should be default move for all other algorithms</li>
</ul>
<li>Computer Player</li>
<ul>
<li>A simple algorithm that makes moves based on certain conditions</li>
<li>Because this game is easy, this algorithm actually plays a perfect game</li>
</ul>
<li>Human Player</li>
<ul>
<li>Prompts the user to enter input for each move</li>
<li>Works just like other algorithms</li>
<li>Allows humans to play computers, and other fun combinations</li>
</ul>
</ul>

### Create Your Own Algorithm

Tic Tac Toe is an easy game, so the algorithms aren't hard to write. If you would like to create your own for fun, create a C++ class that inherits from the abstract base class <code>Player</code>. You must implement the <code>getMove()</code> method on your new class, which the game engine will use to get your move each turn. The current game board will be passed to you as a parameter, and you must return a new game board with your desired move. The game engine checks to make sure that all moves made are valid.

You can determine which player you are using the <code>getPlayerBoardValue()</code> method implemented on the Player class. This returns a <code>BoardValue</code> which is an enumeration defined in <i>utilities.cpp</i>. Your opponents board value is also available.

```c++
class Player
{
	private:
	
	BoardValue playerBoardValue;
	BoardValue opponentBoardValue;
	
	public:
	
	virtual Board getMove(const Board &) = 0;
	
	void setPlayerBoardValue(BoardValue playerBoardValue)
	{
		this->playerBoardValue = playerBoardValue;
		this->opponentBoardValue = this->playerBoardValue == BoardValue::X ? BoardValue::O : BoardValue::X;
	}
	
	BoardValue getPlayerBoardValue()
	{
		return this->playerBoardValue;
	}
	
	BoardValue getOpponentBoardValue()
	{
		return this->playerBoardValue;
	}
};
```
