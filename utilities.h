#include <iostream>
#include <algorithm>
#include <vector>

#ifndef __UTILITIES
#define __UTILITIES

enum GameResult {PlayerOneWin, PlayerTwoWin, Tie};
enum BoardValue {Empty, X, O};

const unsigned BOARD_SIZE = 3;
typedef std::vector<std::vector<BoardValue> > IBoard;

void printBoard(const IBoard & board);
IBoard copyBoard(const IBoard & original);
IBoard createNewBoard();
bool playerHasWon(const IBoard & board, unsigned player);
bool boardIsInWinningState(const IBoard & board);
unsigned numAvailableMoves(const IBoard & board);
bool validMove(const IBoard & board, const IBoard & boardAfterPlayerMove, BoardValue playerBoardValue);

void printBoard(const IBoard & board)
{
	std::cout << '\n';
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

IBoard copyBoard(const IBoard & original)
{
	IBoard copyBoard = createNewBoard();
	
	std::copy(original.begin(), original.begin() + BOARD_SIZE, copyBoard.begin());
	
	return copyBoard;
}

IBoard createNewBoard()
{
	return {{Empty, Empty, Empty}, {Empty, Empty, Empty}, {Empty, Empty, Empty}};
}

bool playerHasWon(const IBoard & board, BoardValue playerBoardValue)
{
	bool won = false;
	
	for(unsigned row = 0; row < BOARD_SIZE; row++) if(board[row][0] == playerBoardValue && board[row][1] == playerBoardValue && board[row][2] == playerBoardValue) won = true;
	for(unsigned column = 0; column < BOARD_SIZE; column++) if(board[0][column] == playerBoardValue && board[1][column] == playerBoardValue && board[2][column] == playerBoardValue) won = true;
	if(board[0][0] == playerBoardValue && board[1][1] == playerBoardValue && board[2][2] == playerBoardValue) won = true;
	if(board[0][2] == playerBoardValue && board[1][1] == playerBoardValue && board[2][0] == playerBoardValue) won = true;
	
	return won;
}

bool boardIsInWinningState(const IBoard & board)
{
	return playerHasWon(board, BoardValue::O) || playerHasWon(board, BoardValue::X);
}

unsigned numAvailableMoves(const IBoard & board)
{
	unsigned availableMoves = 0;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++) for(unsigned j = 0; j < BOARD_SIZE; j++) if(board[i][j] == 0) availableMoves++;
	
	return availableMoves;
}

bool validMove(const IBoard & board, const IBoard & boardAfterPlayerMove, BoardValue playerBoardValue)
{
	unsigned numDifferences = 0;
	bool moveMatchesPlayer = false;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++) for(unsigned j = 0; j < BOARD_SIZE; j++) if(board[i][j] != boardAfterPlayerMove[i][j]) numDifferences++;
	
	if(numDifferences == 1)
	{
		for(unsigned i = 0; i < BOARD_SIZE; i++)
		{
			for(unsigned j = 0; j < BOARD_SIZE; j++)
			{
				if(board[i][j] != boardAfterPlayerMove[i][j])
				{
					if (board[i][j] != BoardValue::Empty) return false;
					if (boardAfterPlayerMove[i][j] == playerBoardValue) moveMatchesPlayer = true;
				}
			}
		}
	}
	else return false;
	
	return moveMatchesPlayer;
}

#endif