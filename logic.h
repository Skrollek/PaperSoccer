#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "board.h"

Direction oppositeDirection(Direction direction);
bool bounce(Board *board, uint16_t xTarget, uint16_t yTarget);
bool directionOccupied(Board* board, uint16_t xStart, uint16_t yStart, Direction direction);
Direction coordsToDirection(uint16_t xStart, uint16_t yStart,  uint16_t xTarget, uint16_t yTarget);
bool isMovePossible(Board* board, uint16_t xStart, uint16_t yStart,  uint16_t xTarget, uint16_t yTarget);
uint8_t calculatePossibleMoves(Board *board, uint16_t xStart, uint16_t yStart);

#endif