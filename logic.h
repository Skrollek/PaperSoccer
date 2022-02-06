#ifndef LOGIC_H
#define LOGIC_H
#include "libs.h"

Direction oppositeDirection(Direction direction);
bool bounce(Board *board, uint16_t xTarget, uint16_t yTarget);
bool directionOccupied(Board* board, uint16_t xStart, uint16_t yStart, Direction direction);
Direction coordsToDirection(uint16_t xStart, uint16_t yStart,  uint16_t xTarget, uint16_t yTarget);
bool isMovePossible(Board* board, uint16_t xStart, uint16_t yStart,  Direction direction);
int32_t directionToCoords(Direction direction); // returns x coord on bits from 31 to 16, and y coord on bits from 15 to 0. 0x7FFF7FFF if direction was equal to "error"
int16_t getXCoordFromInt(uint32_t coords); 
int16_t getYCoordFromInt(uint32_t coords);
uint8_t calculatePossibleMoves(Board *board, uint16_t xStart, uint16_t yStart);
bool gameEnded(Board *board);
bool declareWinner(Board *board);
void boardCatchUpToMoves(Board* board);


#endif