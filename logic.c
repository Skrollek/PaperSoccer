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

int32_t directionToCoords(Direction direction) // returns x coord on bits from 31 to 16, and y coord on bits from 15 to 0. 0x7FFFFFF if direction was equal to "error"
{
    switch (direction)
    {
    case North:
        return 1;
    case NorthEast:
        return (1 << 16) | 1;
    case East:
        return (1 << 16);
    case SouthEast:
        return (1 << 16) | (uint16_t)(-1); 
    case South:
        return (uint16_t)(-1); 
    case SouthWest:
        return ((uint16_t)(-1) << 16) | (uint16_t)(-1);
    case West:
        return ((uint16_t)(-1) << 16);
    case NorthWest:
        return ((uint16_t)(-1) << 16) | 1;
    default:
        return 0x7FFFFFF;
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

