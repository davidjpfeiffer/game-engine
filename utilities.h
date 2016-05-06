#ifndef __UTILITIES
#define __UTILITIES

#include <iostream>
#include <vector>
#include <utility>

const unsigned BOARD_SIZE = 3;

enum GameResult {PlayerOneWin, PlayerTwoWin, Tie};
enum BoardValue {Empty, O, X};

typedef std::vector<std::vector<BoardValue> > Board;

void printBoard(const Board & board);
Board copyBoard(const Board & original);
Board createNewBoard();
bool playerHasWon(const Board & board, unsigned player);
bool boardIsInWinningState(const Board & board);
unsigned numAvailableMoves(const Board & board);
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
				case BoardValue::X:
					std::cout << "  X  ###";
					break;
				case BoardValue::O:
					std::cout << "  O  ###";
					break;
			}
		}
		std::cout << "\n###     ###     ###     ###\n";
	}
	std::cout << "###########################\n";
	std::cout << '\n';
}

Board copyBoard(const Board & original)
{
	Board copyBoard = createNewBoard();
	
	std::copy(original.begin(), original.begin() + BOARD_SIZE, copyBoard.begin());
	
	return copyBoard;
}

Board createNewBoard()
{
	return {{BoardValue::Empty, BoardValue::Empty, BoardValue::Empty}, {BoardValue::Empty, BoardValue::Empty, BoardValue::Empty}, {BoardValue::Empty, BoardValue::Empty, BoardValue::Empty}};
}

bool playerHasWon(const Board & board, BoardValue playerBoardValue)
{
	bool won = false;
	
	for(unsigned row = 0; row < BOARD_SIZE; row++) if(board[row][0] == playerBoardValue && board[row][1] == playerBoardValue && board[row][2] == playerBoardValue) won = true;
	for(unsigned column = 0; column < BOARD_SIZE; column++) if(board[0][column] == playerBoardValue && board[1][column] == playerBoardValue && board[2][column] == playerBoardValue) won = true;
	if(board[0][0] == playerBoardValue && board[1][1] == playerBoardValue && board[2][2] == playerBoardValue) won = true;
	if(board[0][2] == playerBoardValue && board[1][1] == playerBoardValue && board[2][0] == playerBoardValue) won = true;
	
	return won;
}

bool boardIsInWinningState(const Board & board)
{
	return playerHasWon(board, BoardValue::O) || playerHasWon(board, BoardValue::X);
}

unsigned numAvailableMoves(const Board & board)
{
	unsigned availableMoves = 0;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++) for(unsigned j = 0; j < BOARD_SIZE; j++) if(board[i][j] == 0) availableMoves++;
	
	return availableMoves;
}

bool validMove(const Board & board, const Board & boardAfterPlayerMove, BoardValue playerBoardValue)
{
	unsigned numDifferences = 0;
	bool moveMatchesPlayer = false;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++)
		for(unsigned j = 0; j < BOARD_SIZE; j++)
			if(board[i][j] != boardAfterPlayerMove[i][j]) numDifferences++;
	
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

Board makeRandomMove(const Board & board, BoardValue playerBoardValue)
{
	Board newBoard = copyBoard(board);
	std::vector<std::pair<unsigned, unsigned> > availableMoves;
	
	for(unsigned i = 0; i < BOARD_SIZE; i++)
	{
		for(unsigned j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == BoardValue::Empty) availableMoves.push_back(std::make_pair(i, j));
		}
	}
	
	unsigned randomMove = getRandomNumber(availableMoves.size() - 1);
	
	newBoard[availableMoves[randomMove].first][availableMoves[randomMove].second] = playerBoardValue;
	
	return newBoard;
}

unsigned getRandomNumber(unsigned mod)
{
	if (mod == 0) return 0;
	else return rand() % mod;
}

#endif