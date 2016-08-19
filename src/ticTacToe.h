#ifndef __TICTACTOE
#define __TICTACTOE

#include <iostream>
#include <vector>
#include "player.h"
#include "gameState.h"
#include "gameResult.h"
#include "utilities.h"

class TicTacToe
{
public:
  
  // Abstract Game Class Methods
  
  void setupPlayers(Player & playerOne, Player & playerTwo)
  {
    playerOne.setPlayerValue(PlayerValue::PlayerOne);
    playerTwo.setPlayerValue(PlayerValue::PlayerTwo);
  }
  
  static bool isOver(const GameState & gameState)
  {
    return gameState.board.numberOfAvailableMoves() == 0 || playerHasWon(gameState, PlayerValue::PlayerOne) || playerHasWon(gameState, PlayerValue::PlayerTwo);
  }
  
  static bool isValidMove(const GameState & gameStateBeforeMove, const GameState & gameStateAfterMove, const PlayerValue & playerValue)
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
            if (isPlayersBoardValue(playerValue, gameStateAfterMove.board.get(i, j)))
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
  
  static bool playerHasWon(const GameState & gameState, const PlayerValue & playerValue)
  {
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      if ( isPlayersBoardValue(playerValue, gameState.board.get(row, 0))
        && isPlayersBoardValue(playerValue, gameState.board.get(row, 1))
        && isPlayersBoardValue(playerValue, gameState.board.get(row, 2)))
      {
        return true;
      }
    }

    for (unsigned column = 0; column < BOARD_SIZE; column++)
    {
      if ( isPlayersBoardValue(playerValue, gameState.board.get(0, column))
        && isPlayersBoardValue(playerValue, gameState.board.get(1, column))
        && isPlayersBoardValue(playerValue, gameState.board.get(2, column)))
      {
        return true;
      }
    }

    if ( isPlayersBoardValue(playerValue, gameState.board.get(0, 0))
      && isPlayersBoardValue(playerValue, gameState.board.get(1, 1))
      && isPlayersBoardValue(playerValue, gameState.board.get(2, 2)))
    {
      return true;
    }

    if ( isPlayersBoardValue(playerValue, gameState.board.get(0, 2))
      && isPlayersBoardValue(playerValue, gameState.board.get(1, 1))
      && isPlayersBoardValue(playerValue, gameState.board.get(2, 0)))
    {
      return true;
    }

    return false;
  }
  
  // Custom Methods
  
  static GameState makeRandomMove(const GameState & gameState, const PlayerValue & playerValue)
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

    gameStateAfterMove.board.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerValueToBoardValue(playerValue));

    return gameStateAfterMove;
  }
  
  static bool isPlayersBoardValue(const PlayerValue & playerValue, const BoardValue & boardValue)
  {
    return playerValue == PlayerValue::PlayerOne ? boardValue == BoardValue::O : boardValue == BoardValue::X;
  }
  
  static BoardValue playerValueToBoardValue(PlayerValue playerValue)
  {
    if (playerValue == PlayerValue::PlayerOne) return BoardValue::O;
    else return BoardValue::X;
  }
  
  static PlayerValue boardValueToPlayerValue(BoardValue boardValue)
  {
    if (boardValue == BoardValue::O) return PlayerValue::PlayerOne;
    else if (boardValue == BoardValue::X) return PlayerValue::PlayerTwo;
    else exitWithErrorMessage("Invalid board value passed to BoardValueToPlayerOrder method.");
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
};

#endif