#ifndef __TICTACTOE
#define __TICTACTOE

#include <iostream>
#include <vector>
#include "gameState.h"
#include "gameResult.h"
#include "utilities.h"

class TicTacToe
{
public:
  
  // Abstract Game Class Methods
  
  static bool isOver(const GameState & gameState)
  {
    return gameState.board.numberOfAvailableMoves() == 0 || playerOneHasWon(gameState) || playerTwoHasWon(gameState);
  }
  
  static bool isValidMove(const GameState & gameStateBeforeMove, const GameState & gameStateAfterMove, const BoardValue & playerBoardValue)
  {
    if (numberOfDifferencesBetweenBoards(gameStateBeforeMove.board, gameStateAfterMove.board) == 1)
    {
      for (unsigned i = 0; i < BOARD_SIZE; i++)
      {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
          if (gameStateBeforeMove.board.get(i, j) != gameStateAfterMove.board.get(i, j))
          {
            if (gameStateBeforeMove.board.get(i, j) != BoardValue::Empty)
            {
              return false;
            }
            if (gameStateAfterMove.board.get(i, j) == playerBoardValue)
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
  
  static bool playerOneHasWon(const GameState & gameState)
  {
    return playerHasWon(gameState, BoardValue::PlayerOne);
  }
  
  static bool playerTwoHasWon(const GameState & gameState)
  {
    return playerHasWon(gameState, BoardValue::PlayerTwo);
  }
  
  // Custom Methods
  
  static GameState makeRandomMove(const GameState & gameState, BoardValue playerBoardValue)
  {
    GameState gameStateAfterMove = gameState;
    
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (gameState.board.get(i, j) == BoardValue::Empty)
        {
          availableMoves.push_back(std::make_pair(i, j));
        }
      }
    }

    unsigned randomMove = getRandomNumber(availableMoves.size() - 1);

    gameStateAfterMove.board.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerBoardValue);

    return gameStateAfterMove;
  }

  static char getBoardValueAsChar(BoardValue boardValue)
  {
    switch (boardValue)
    {
      case BoardValue::PlayerOne:
        return '1';
      case BoardValue::PlayerTwo:
        return '2';
      default:
        return '0';
    }
  }
  
private:

  static unsigned numberOfDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo)
  {
    unsigned numDifferences = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (boardOne.get(i, j) != boardTwo.get(i, j))
        {
          numDifferences++;
        }
      }
    }

    return numDifferences;
  }

  static bool playerHasWon(const GameState & gameState, BoardValue playerBoardValue)
  {
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      if (gameState.board.get(row, 0) == playerBoardValue && gameState.board.get(row, 1) == playerBoardValue && gameState.board.get(row, 2) == playerBoardValue)
      {
        return true;
      }
    }

    for (unsigned column = 0; column < BOARD_SIZE; column++)
    {
      if (gameState.board.get(0, column) == playerBoardValue && gameState.board.get(1, column) == playerBoardValue && gameState.board.get(2, column) == playerBoardValue)
      {
        return true;
      }
    }

    if (gameState.board.get(0, 0) == playerBoardValue && gameState.board.get(1, 1) == playerBoardValue && gameState.board.get(2, 2) == playerBoardValue)
    {
      return true;
    }

    if (gameState.board.get(0, 2) == playerBoardValue && gameState.board.get(1, 1) == playerBoardValue && gameState.board.get(2, 0) == playerBoardValue)
    {
      return true;
    }

    return false;
  }
};

#endif