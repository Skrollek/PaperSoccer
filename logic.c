#include "libs.h"
#include "logic.h"

Direction oppositeDirection(Direction direction)
{
    if(direction == Error) return Error;
    return (direction + 4)%8;
}

bool bounce(Board *board, uint16_t xTarget, uint16_t yTarget)
{
    return *boardVisitedAt(board, xTarget, yTarget);
}

bool directionOccupied(Board* board, uint16_t xStart, uint16_t yStart, Direction direction)
{
    return *boardDirectionUsedAt(board, xStart, yStart, direction);
}

Direction coordsToDirection(uint16_t xStart, uint16_t yStart, uint16_t xTarget, uint16_t yTarget)
{
    if      ((xStart == xTarget) && (yStart - 1 == yTarget))     { return North; }
    else if ((xStart + 1 == xTarget) && (yStart - 1 == yTarget)) { return NorthEast; }
    else if ((xStart + 1 == xTarget) && (yStart == yTarget))     { return East; }
    else if ((xStart + 1 == xTarget) && (yStart + 1 == yTarget)) { return SouthEast; }
    else if ((xStart == xTarget) && (yStart + 1 == yTarget))     { return South; }
    else if ((xStart - 1 == xTarget) && (yStart + 1 == yTarget)) { return SouthWest; }
    else if ((xStart - 1 == xTarget) && (yStart == yTarget))     { return West; }
    else if ((xStart - 1 == xTarget) && (yStart - 1 == yTarget)) { return NorthWest; }
    else return Error;
}

int32_t directionToCoords(Direction direction) // returns x coord on bits from 31 to 16, and y coord on bits from 15 to 0. 0x7FFF7FFF if direction was equal to "error"
{
    switch (direction)
    {
    case North:
        return (0 << 16)              | (uint16_t)(-1);
    case NorthEast:
        return (1 << 16)              | (uint16_t)(-1);
    case East:
        return (1 << 16)              | 0;
    case SouthEast:
        return (1 << 16)              | 1; 
    case South:
        return (0 << 16)              | 1; 
    case SouthWest:
        return ((uint16_t)(-1) << 16) | 1;
    case West:
        return ((uint16_t)(-1) << 16) | 0;
    case NorthWest:
        return ((uint16_t)(-1) << 16) | (uint16_t)(-1);
    default:
        return 0x7FFF7FFF;
    }
}

int16_t getXCoordFromInt(uint32_t coords)
{
    if((coords >> 16) == 1) return 1;
    if((coords >> 16) == (uint16_t)(-1)) return -1;
    return 0;
}
int16_t getYCoordFromInt(uint32_t coords)
{
    if(((coords << 16) >> 16) == 1) return 1;
    if(((coords << 16) >> 16) == (uint16_t)(-1)) return -1;
    return 0;
}

bool isMovePossible(Board* board, uint16_t xStart, uint16_t yStart,  Direction direction)
{   
    if(direction != Error) return !directionOccupied(board, xStart, yStart, direction);
    return false;
}

uint8_t calculatePossibleMoves(Board *board, uint16_t xStart, uint16_t yStart)
{
    uint8_t result = 0;
    for(int i = 0; i < 8; ++i)
    {
        if(isMovePossible(board, xStart, yStart, i))
        {
            result |= 1 << i;
        }
    }
    return result;
}

bool gameEnded(Board *board)
{
    if(board->ballY == 0 || board->ballY == board->height - 1) // x check should not be necessary!
        return true;
    if(calculatePossibleMoves(board, board->ballX, board->ballY) == 0)
        return true;
    return false;
    
}

bool declareWinner(Board *board)
{
    if(calculatePossibleMoves(board, board->ballX, board->ballY) == 0)
        return !board->playerOnMove;
    if(board->ballY == 0)
        return true;
    return false;
}
void boardCatchUpToMoves(Board* board)
{
    board->playerOnMove = 0;
    int i = 0;
    board->ballX = board->width/2;
    board->ballY = board->height/2;
    while(i < board->it)
    {
        if(board->moves[i] == '#')
        {
            board->playerOnMove = !board->playerOnMove;
        }
        else if(board->moves[i] != ' ')
        {
            Direction direction = board->moves[i] - '0';
            uint32_t coords = directionToCoords(direction);
            *boardDirectionUsedAt(board, board->ballX, board->ballY, direction) = 1;
            board->ballX += getXCoordFromInt(coords);
            board->ballY += getYCoordFromInt(coords);
            *boardDirectionUsedAt(board, board->ballX, board->ballY, oppositeDirection(direction)) = 1;
            *boardVisitedAt(board, board->ballX, board->ballY) = 1;
        }
        ++i;
    }
}

