#ifndef __UTILITIES
#define __UTILITIES

#include <iostream>
#include <vector>
#include <utility>

const unsigned BOARD_SIZE = 3;

enum GameResult {Tie, PlayerOneWin, PlayerTwoWin};
enum BoardValue {Empty, PlayerOne, PlayerTwo};
enum GameType {Single, Multiple};

typedef std::vector<std::vector<BoardValue> > Board;

void printBoard(const Board & board);
Board createCopyOfBoard(const Board & original);
Board createEmptyBoard();
bool playerHasWon(const Board & board, unsigned player);
bool boardIsInWinningState(const Board & board);
unsigned numAvailableMoves(const Board & board);
unsigned numDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo);
bool validMove(const Board & board, const Board & boardAfterPlayerMove, BoardValue playerBoardValue);
Board makeRandomMove(const Board & board);
unsigned getRandomNumber(unsigned mod);

void printBoard(const Board & board)
{
	std::cout << '\n';
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << "###########################\n";
		std::cout << "###     ###     ###     ###\n";
		std::cout << "###";
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			switch(board[i][j])
			{
				case BoardValue::Empty:
					std::cout << "     ###";
					break;
				case BoardValue::PlayerOne:
					std::cout << "  O  ###";
					break;
				case BoardValue::PlayerTwo:
					std::cout << "  X  ###";
					break;
			}
		}
		std::cout << "\n###     ###     ###     ###\n";
	}
	std::cout << "###########################\n\n";
}

Board createCopyOfBoard(const Board & original)
{
	Board copy = createEmptyBoard();
	
	std::copy(original.begin(), original.begin() + BOARD_SIZE, copy.begin());
	
	return copy;
}

Board createEmptyBoard()
{
	return {{ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
			{ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
			{ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty }};
}

bool playerHasWon(const Board & board, BoardValue playerBoardValue)
{
	bool won = false;
	
	for(unsigned row = 0; row < BOARD_SIZE; row++)
	{
		if(board[row][0] == playerBoardValue && board[row][1] == playerBoardValue && board[row][2] == playerBoardValue)
		{
			won = true;
		}
	}
	
	for(unsigned column = 0; column < BOARD_SIZE; column++)
	{
		if(board[0][column] == playerBoardValue && board[1][column] == playerBoardValue && board[2][column] == playerBoardValue)
		{
			won = true;
		}
	}
	
	if(board[0][0] == playerBoardValue && board[1][1] == playerBoardValue && board[2][2] == playerBoardValue)
	{
		won = true;
	}
	
	if(board[0][2] == playerBoardValue && board[1][1] == playerBoardValue && board[2][0] == playerBoardValue)
	{
		won = true;
	}
	
	return won;
}

bool boardIsInWinningState(const Board & board)
{
	return playerHasWon(board, BoardValue::PlayerOne) || playerHasWon(board, BoardValue::PlayerTwo);
}

unsigned numAvailableMoves(const Board & board)
{
	unsigned availableMoves = 0;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			if(board[i][j] == BoardValue::Empty)
			{
				availableMoves++;
			}
		}
	}
	
	return availableMoves;
}

unsigned numDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo)
{
	unsigned numDifferences = 0;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			if(boardOne[i][j] != boardTwo[i][j])
			{
				numDifferences++;
			}
		}
	}
	
	return numDifferences;
}

bool validMove(const Board & board, const Board & boardAfterPlayerMove, BoardValue playerBoardValue)
{
	if(numDifferencesBetweenBoards(board, boardAfterPlayerMove) == 1)
	{
		for(unsigned i = 0; i < BOARD_SIZE; i++)
		{
			for(unsigned j = 0; j < BOARD_SIZE; j++)
			{
				if(board[i][j] != boardAfterPlayerMove[i][j])
				{
					if (board[i][j] != BoardValue::Empty)
					{
						return false;
					}
					if (boardAfterPlayerMove[i][j] == playerBoardValue)
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

Board makeRandomMove(const Board & board, BoardValue playerBoardValue)
{
	Board newBoard = createCopyOfBoard(board);
	std::vector<std::pair<unsigned, unsigned> > availableMoves;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == BoardValue::Empty)
			{
				availableMoves.push_back(std::make_pair(i, j));
			}
		}
	}
	
	unsigned randomMove = getRandomNumber(availableMoves.size() - 1);
	
	newBoard[availableMoves[randomMove].first][availableMoves[randomMove].second] = playerBoardValue;
	
	return newBoard;
}

unsigned getRandomNumber(unsigned mod)
{
	if (mod == 0)
	{
		return 0;
	}
	else
	{
		return rand() % mod;
	}
}

#endif