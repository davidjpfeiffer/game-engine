#ifndef __TICTACTOEGAMEDEFINITION
#define __TICTACTOEGAMEDEFINITION

#include <iostream>
#include <vector>

#include "../../GameEngine/gameDefinition.h"
#include "../../GameEngine/Utilities/randomNumberGenerator.h"

#include "ticTacToeGameState.h"
#include "ticTacToeBoard.h"
#include "ticTacToeBoardValue.h"

class TicTacToeGameDefinition : public GameDefinition
{
  public:
  
  bool isOver(GameState * gameState) const
  {
    return noAvailableMoves(gameState) || playerOneHasWon(gameState) || playerTwoHasWon(gameState);
  }
  
  bool isValidMove(GameState * p_gameStateBeforeMove, GameState * p_gameStateAfterMove, const PlayerValue & playerValue) const
  {
    TicTacToeGameState * gameStateBeforeMove = (TicTacToeGameState *)p_gameStateBeforeMove;
    TicTacToeGameState * gameStateAfterMove = (TicTacToeGameState *)p_gameStateAfterMove;
    
    if (oneMoveWasMadeByPlayer(gameStateBeforeMove, gameStateAfterMove, playerValue))
    {
      for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
      {
        for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
        {
          if (gameStateBeforeMove->board.get(i, j) != gameStateAfterMove->board.get(i, j))
          {
            if (gameStateBeforeMove->board.get(i, j) != TicTacToeBoardValueEmpty)
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
  
  bool playerHasWon(GameState * p_gameState, const PlayerValue & playerValue) const
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
    for (unsigned row = 0; row < TicTacToeBoard::BOARD_SIZE; row++)
    {
      if ( isPlayersBoardValue(playerValue, gameState->board.get(row, 0))
        && isPlayersBoardValue(playerValue, gameState->board.get(row, 1))
        && isPlayersBoardValue(playerValue, gameState->board.get(row, 2)))
      {
        return true;
      }
    }

    for (unsigned column = 0; column < TicTacToeBoard::BOARD_SIZE; column++)
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
  
  GameState * getInitialGameState() const
  {
    return new TicTacToeGameState;
  }
  
  void makeRandomMove(GameState * p_gameState, const PlayerValue & playerValue) const
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
      {
        if (gameState->board.get(i, j) == TicTacToeBoardValueEmpty)
        {
          availableMoves.push_back(std::make_pair(i, j));
        }
      }
    }
    
    unsigned randomMove = RandomNumberGenerator::instance()->get(availableMoves.size() - 1);
    
    gameState->board.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerValueToBoardValue(playerValue));
  }
  
  bool isPlayersBoardValue(const PlayerValue & playerValue, const TicTacToeBoardValue & boardValue) const
  {
    return playerValue == PlayerValue::PlayerOne ? boardValue == TicTacToeBoardValuePlayerOne : boardValue == TicTacToeBoardValuePlayerTwo;
  }
  
  TicTacToeBoardValue playerValueToBoardValue(PlayerValue playerValue) const
  {
    return playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValuePlayerOne : TicTacToeBoardValuePlayerTwo;
  }
  
  PlayerValue boardValueToPlayerValue(TicTacToeBoardValue boardValue) const
  {
    return boardValue == TicTacToeBoardValuePlayerOne ? PlayerValue::PlayerOne : PlayerValue::PlayerTwo;
  }
  
  private:
  
  bool noAvailableMoves(GameState * p_gameState) const
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    
    return gameState->board.getAvailableMoves().size() == 0;
  }
  
  bool playerOneHasWon(GameState * gameState) const
  {
    return playerHasWon(gameState, PlayerValue::PlayerOne);
  }
  
  bool playerTwoHasWon(GameState * gameState) const
  {
    return playerHasWon(gameState, PlayerValue::PlayerTwo);
  }
  
  bool oneMoveWasMadeByPlayer(GameState * p_gameStateBeforeMove, GameState * p_gameStateAfterMove, const PlayerValue & playerValue) const
  {
    TicTacToeGameState * gameStateBeforeMove = (TicTacToeGameState *)p_gameStateBeforeMove;
    TicTacToeGameState * gameStateAfterMove = (TicTacToeGameState *)p_gameStateAfterMove;
    
    unsigned oneMoveMade = numberOfDifferencesBetweenBoards(gameStateBeforeMove->board, gameStateAfterMove->board) == 1;
    bool byPlayer = moveWasMadeByPlayer(gameStateBeforeMove->board, gameStateAfterMove->board, playerValue);
    
    return oneMoveMade && byPlayer;
  }
  
  unsigned numberOfDifferencesBetweenBoards(const TicTacToeBoard & boardOne, const TicTacToeBoard & boardTwo) const
  {
    unsigned numDifferences = 0;

    for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
      {
        if (boardOne.get(i, j) != boardTwo.get(i, j))
        {
          numDifferences++;
        }
      }
    }

    return numDifferences;
  }
  
  bool moveWasMadeByPlayer(const TicTacToeBoard & boardOne, const TicTacToeBoard & boardTwo, const PlayerValue & playerValue) const
  {
    TicTacToeBoardValue boardValue = playerValueToBoardValue(playerValue);
    unsigned beforeCount = 0, afterCount = 0;
    
    for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
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