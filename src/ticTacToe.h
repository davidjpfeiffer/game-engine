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
  
  void newGameState(GameState ** p_gameState)
  {
    * p_gameState = new TicTacToeGameState;
  }
  
  void copyGameState(GameState * p_gameStateOriginal, GameState * p_gameStateCopy)
  {
    TicTacToeGameState * gameStateOriginal = (TicTacToeGameState *)p_gameStateOriginal;
    TicTacToeGameState * gameStateCopy = (TicTacToeGameState *)p_gameStateCopy;
    gameStateCopy->board = gameStateOriginal->board;
  }
  
  bool isNotOver(GameState * gameState)
  {
    return availableMoves(gameState) && playerOneHasNotWon(gameState) && playerTwoHasNotWon(gameState);
  }
  
  bool isValidMove(GameState * p_gameStateBeforeMove, GameState * p_gameStateAfterMove, const PlayerValue & playerValue)
  {
    TicTacToeGameState * gameStateBeforeMove = (TicTacToeGameState *)p_gameStateBeforeMove;
    TicTacToeGameState * gameStateAfterMove = (TicTacToeGameState *)p_gameStateAfterMove;
    
    if (oneMoveWasMadeByPlayer(gameStateBeforeMove, gameStateAfterMove, playerValue))
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
  
  bool playerHasWon(GameState * p_gameState, const PlayerValue & playerValue)
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
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
  
  void makeRandomMove(GameState * p_gameState, const PlayerValue & playerValue)
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
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
    
    gameState->board.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerValueToBoardValue(playerValue));
  }
  
  bool isPlayersBoardValue(const PlayerValue & playerValue, const TicTacToeBoardValue & boardValue)
  {
    return playerValue == PlayerValue::PlayerOne ? boardValue == TicTacToeBoardValue::O : boardValue == TicTacToeBoardValue::X;
  }
  
  TicTacToeBoardValue playerValueToBoardValue(PlayerValue playerValue)
  {
    return playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValue::O : TicTacToeBoardValue::X;
  }
  
  PlayerValue boardValueToPlayerValue(TicTacToeBoardValue boardValue)
  {
    return boardValue == TicTacToeBoardValue::O ? PlayerValue::PlayerOne : PlayerValue::PlayerTwo;
  }
  
  private:
  
  bool availableMoves(GameState * p_gameState)
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
    return gameState->board.numberOfAvailableMoves() > 0;
  }
  
  bool playerOneHasNotWon(GameState * gameState)
  {
    return !playerHasWon(gameState, PlayerValue::PlayerOne);
  }
  
  bool playerTwoHasNotWon(GameState * gameState)
  {
    return !playerHasWon(gameState, PlayerValue::PlayerTwo);
  }
  
  bool oneMoveWasMadeByPlayer(GameState * p_gameStateBeforeMove, GameState * p_gameStateAfterMove, const PlayerValue & playerValue)
  {
    TicTacToeGameState * gameStateBeforeMove = (TicTacToeGameState *)p_gameStateBeforeMove;
    TicTacToeGameState * gameStateAfterMove = (TicTacToeGameState *)p_gameStateAfterMove;
    
    unsigned oneMoveMade = numberOfDifferencesBetweenBoards(gameStateBeforeMove->board, gameStateAfterMove->board) == 1;
    bool byPlayer = moveWasMadeByPlayer(gameStateBeforeMove->board, gameStateAfterMove->board, playerValue);
    
    return oneMoveMade && byPlayer;
  }
  
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
  
  unsigned moveWasMadeByPlayer(const TicTacToeBoard & boardOne, const TicTacToeBoard & boardTwo, const PlayerValue & playerValue)
  {
    TicTacToeBoardValue boardValue = playerValueToBoardValue(playerValue);
    unsigned beforeCount = 0, afterCount = 0;
    
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (boardOne.get(i, j) == boardValue)
        {
          beforeCount++;
        }
        
        if (boardTwo.get(i, j) == boardValue)
        {
          afterCount++;
        }
      }
    }
    
    return beforeCount + 1 == afterCount;
  }
};

#endif