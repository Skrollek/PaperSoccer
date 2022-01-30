#ifndef BOARD_H
#define BOARD_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum Direction
{
    Error = -1, North = 0, NorthEast = 1, East = 2, SouthEast = 3, South = 4, SouthWest = 5, West = 6, NorthWest = 7 // not necessary to write direction = [0,7] but it is easier to read  
} Direction;

typedef struct Board
{
    uint16_t width;
    uint16_t height;
    uint16_t ballX;
    uint16_t ballY;
    bool* visited;
    bool* directionUsed;
} Board;

Board* initializeBoard(uint16_t initialWidth, uint16_t initialHeight);
bool* boardVisitedAt(Board* board, uint16_t x, uint16_t y);
bool* boardDirectionUsedAt(Board* board, uint16_t x, uint16_t y, Direction direction);
void startBoardData(Board* board);
#endif