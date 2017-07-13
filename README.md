## Game Engine

This command line interface program allows two players to play against each other in any given two-player turn-based strategy game. The games are defined by implementing the abstract base class `Game`, which defines the rules for the game. The players implement the abstract base class `Player`, which requires them to implement a get move method that is used by the game engine to get the players move given a game state. The game engine takes care of the details necessary to play the game, while the game and players define the logic for the game itself and how it is played.

This project was originally written for the 2016 Southeast Missouri State Hackathon. It has since been refactored and improved. The program was written to better understand how game engines work and to gain experience designing interfaces for relational objects within a complex system.

### How It Works

There are two components of the game engine: the base components that provide the structure and interfaces necessary for the game engine to play games, and the implementation of these interfaces which includes the games and players themselves. The game engine is responsible for facilitating the playing of games and using the game class to verify players moves. The players themselves implement a single method that returns a move given a game state.

To use the game engine, you need only include the gameEngine.h file and call the `start()` method as illustrated in the main.cpp file. This prompts the user to enter their desired game, the number of games to be played, and the first and second player. The available games are retrieved from the `Game Registry` class, which is just a class that contains a list of all available games. Similarly, each of the games has a `Player Registry` which is used by the game engine to retrieve the available players for any given game. If you add a new game or player, you should update the registry accordingly.

### Games

- Tic Tac Toe
- Connect Four

### Features

- Parallel processing support for multiple games
- Custom exceptions and elegant exception handling
- Display visual game state one move at a time
- Display summary statistics for multiple games

### License

GNU GENERAL PUBLIC LICENSE

ALL RIGHTS RESERVED
