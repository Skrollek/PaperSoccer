#include "board.h"
#include <stdlib.h>

Board* initializeBoard(uint16_t initialWidth, uint16_t initialHeight)
{
    Board* newBoard = (Board*)malloc(sizeof(Board));
    newBoard->width = ++initialWidth;
    newBoard->height = ++initialHeight;
    newBoard->visited = malloc(sizeof(bool)*initialHeight*initialWidth);
    newBoard->directionUsed = malloc(sizeof(bool)*initialHeight*initialWidth*8);
    newBoard->ballX = initialWidth/2;
    newBoard->ballY = initialHeight/2;
    return newBoard;
}

inline bool* boardVisitedAt(Board* board, uint16_t x, uint16_t y)
{
    return &board->visited[x + y * board->width]; // return board->visited + x + y * board->width;
}
inline bool* boardDirectionUsedAt(Board* board, uint16_t x, uint16_t y, Direction direction)
{
    return &board->directionUsed[direction + x * 8 + y * board->width * 8]; // board->directionUsed + z + x * 8 + y * board->width * 8;
}