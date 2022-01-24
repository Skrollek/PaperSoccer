#include "logic.h"

Direction oppositeDirection(Direction direction)
{
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

Direction coordsToDirection(uint16_t xStart, uint16_t yStart,  uint16_t xTarget, uint16_t yTarget)
{
    if      ((xStart == xTarget) && (yStart + 1 == yTarget))     { return North; }
    else if ((xStart + 1 == xTarget) && (yStart + 1 == yTarget)) { return  NorthEast; }
    else if ((xStart + 1 == xTarget) && (yStart == yTarget)) { return East; }
    else if ((xStart + 1 == xTarget) && (yStart - 1 == yTarget)) { return SouthEast; }
    else if ((xStart == xTarget) && (yStart - 1 == yTarget)) { return South; }
    else if ((xStart - 1 == xTarget) && (yStart - 1 == yTarget)) { return SouthWest; }
    else if ((xStart - 1 == xTarget) && (yStart == yTarget)) { return West; }
    else if ((xStart - 1 == xTarget) && (yStart + 1 == yTarget)) { return NorthWest; }
    else return Error;
}

bool isMovePossible(Board* board, uint16_t xStart, uint16_t yStart,  uint16_t xTarget, uint16_t yTarget)
{
    if(abs(xStart - xTarget) > 1 || abs(yStart - yTarget) > 1) return false;
    Direction direction = coordsToDirection(xStart, yStart, xTarget, yTarget);
    if(direction != Error) return directionOccupied(board, xStart, yStart, direction);
    else return false;
}
uint8_t calculatePossibleMoves(Board *board, uint16_t xStart, uint16_t yStart)
{
    uint8_t result;
}