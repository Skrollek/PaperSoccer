#include "board.h"


Board* initializeBoard(uint16_t initialWidth, uint16_t initialHeight)
{
    Board* newBoard = (Board*)malloc(sizeof(Board));
    newBoard->width = ++initialWidth;
    newBoard->height = ++initialHeight;
    newBoard->visited = calloc(initialWidth*initialHeight, sizeof(bool));
    newBoard->directionUsed = calloc(initialWidth*initialHeight*8, sizeof(bool));
    newBoard->ballX = initialWidth/2;
    newBoard->ballY = initialHeight/2;
    return newBoard;
}

bool* boardVisitedAt(Board* board, uint16_t x, uint16_t y)
{
    return &board->visited[x + y * board->width]; // return board->visited + x + y * board->width;
}
bool* boardDirectionUsedAt(Board* board, uint16_t x, uint16_t y, Direction direction)
{
    return &board->directionUsed[x*board->height*8 + y*8 + direction];
}