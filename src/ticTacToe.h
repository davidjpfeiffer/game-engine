#ifndef __TICTACTOE
#define __TICTACTOE

#include <iostream>
#include <vector>
#include "game.h"
#include "ticTacToeGameState.h"
#include "ticTacToeBoard.h"
#include "ticTacToeBoardValue.h"
#include "gameResult.h"
#include "utilities.h"

class TicTacToe : public Game
{
public:
  
  // Abstract Game Class Methods
  
  void setupPlayers(Player & playerOne, Player & playerTwo)
  {
    playerOne.setPlayerValue(PlayerValue::PlayerOne);
    playerTwo.setPlayerValue(PlayerValue::PlayerTwo);
  }
  
  bool isOver(GameState * gameState)
  {
    TicTacToeGameState ticTacToeGameState = * gameState;
    
    return ticTacToeGameState.board.numberOfAvailableMoves() == 0 || playerHasWon(& ticTacToeGameState, PlayerValue::PlayerOne) || playerHasWon(& ticTacToeGameState, PlayerValue::PlayerTwo);
  }
  
  bool isValidMove(TicTacToeGameState * gameStateBeforeMove, TicTacToeGameState * gameStateAfterMove, const PlayerValue & playerValue)
  {
    if (numberOfDifferencesBetweenBoards(gameStateBeforeMove->board, gameStateAfterMove->board) == 1)
    {
      for (unsigned i = 0; i < BOARD_SIZE; i++)
      {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
          if (gameStateBeforeMove->board.get(i, j) != gameStateAfterMove->board.get(i, j))
          {
            if (gameStateBeforeMove->board.get(i, j) != TicTacToeBoardValue::Empty)
            {
              return false;
            }
            if (isPlayersBoardValue(playerValue, gameStateAfterMove->board.get(i, j)))
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
  
  bool playerHasWon(TicTacToeGameState * gameState, const PlayerValue & playerValue)
  {
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      if ( isPlayersBoardValue(playerValue, gameState->board.get(row, 0))
        && isPlayersBoardValue(playerValue, gameState->board.get(row, 1))
        && isPlayersBoardValue(playerValue, gameState->board.get(row, 2)))
      {
        return true;
      }
    }

    for (unsigned column = 0; column < BOARD_SIZE; column++)
    {
      if ( isPlayersBoardValue(playerValue, gameState->board.get(0, column))
        && isPlayersBoardValue(playerValue, gameState->board.get(1, column))
        && isPlayersBoardValue(playerValue, gameState->board.get(2, column)))
      {
        return true;
      }
    }

    if ( isPlayersBoardValue(playerValue, gameState->board.get(0, 0))
      && isPlayersBoardValue(playerValue, gameState->board.get(1, 1))
      && isPlayersBoardValue(playerValue, gameState->board.get(2, 2)))
    {
      return true;
    }

    if ( isPlayersBoardValue(playerValue, gameState->board.get(0, 2))
      && isPlayersBoardValue(playerValue, gameState->board.get(1, 1))
      && isPlayersBoardValue(playerValue, gameState->board.get(2, 0)))
    {
      return true;
    }

    return false;
  }
  
  // Custom Methods
  
  GameState * makeRandomMove(TicTacToeGameState * gameState, const PlayerValue & playerValue)
  {
    TicTacToeGameState gameStateAfterMove = * gameState;
    
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (gameState->board.get(i, j) == TicTacToeBoardValue::Empty)
        {
          availableMoves.push_back(std::make_pair(i, j));
        }
      }
    }

    unsigned randomMove = getRandomNumber(availableMoves.size() - 1);

    gameStateAfterMove.board.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerValueToBoardValue(playerValue));

    return & gameStateAfterMove;
  }
  
  bool isPlayersBoardValue(const PlayerValue & playerValue, const TicTacToeBoardValue & boardValue)
  {
    return playerValue == PlayerValue::PlayerOne ? boardValue == TicTacToeBoardValue::O : boardValue == TicTacToeBoardValue::X;
  }
  
  TicTacToeBoardValue playerValueToBoardValue(PlayerValue playerValue)
  {
    if (playerValue == PlayerValue::PlayerOne) return TicTacToeBoardValue::O;
    else return TicTacToeBoardValue::X;
  }
  
  PlayerValue boardValueToPlayerValue(TicTacToeBoardValue boardValue)
  {
    if (boardValue == TicTacToeBoardValue::O) return PlayerValue::PlayerOne;
    else if (boardValue == TicTacToeBoardValue::X) return PlayerValue::PlayerTwo;
    else exitWithErrorMessage("Invalid board value passed to BoardValueToPlayerOrder method.");
  }
  
private:

  unsigned numberOfDifferencesBetweenBoards(const TicTacToeBoard & boardOne, const TicTacToeBoard & boardTwo)
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