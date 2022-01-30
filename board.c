#include "board.h"
Board* initializeBoard(uint16_t initialWidth, uint16_t initialHeight)
{
    Board* newBoard = (Board*)malloc(sizeof(Board));
    newBoard->width = ++initialWidth;
    newBoard->height = ++initialHeight;
    return newBoard;
}
void startBoardData(Board* board)
{
    board->visited = calloc((board->width)*(board->height), sizeof(bool));
    board->directionUsed = calloc((board->width)*(board->height)*8, sizeof(bool));
    board->ballX = board->width/2;
    board->ballY = board->height/2;
    
    // inserting base data
    // left and right border
    for(int y = 0; y < board->height; ++y)
    {
        *boardVisitedAt(board, 0, y) = 1;
        *boardVisitedAt(board, board->width - 1, y) = 1;
        
        *boardDirectionUsedAt(board, 0, y, North) = 1;
        *boardDirectionUsedAt(board, 0, y, South) = 1;
        *boardDirectionUsedAt(board, 0, y, West) = 1;
        *boardDirectionUsedAt(board, 0, y, NorthWest) = 1;
        *boardDirectionUsedAt(board, 0, y, SouthWest) = 1;

        *boardDirectionUsedAt(board, board->width - 1, y, North) = 1;
        *boardDirectionUsedAt(board, board->width - 1, y, South) = 1;
        *boardDirectionUsedAt(board, board->width - 1, y, East) = 1;
        *boardDirectionUsedAt(board, board->width - 1, y, NorthEast) = 1;
        *boardDirectionUsedAt(board, board->width - 1, y, SouthEast) = 1;
    }
    // top and bottom border
    for(int x = 0; x < board->width; ++x)
    {
        *boardVisitedAt(board, x, 0) = 1;
        *boardVisitedAt(board, x, board->height - 1) = 1;

        *boardDirectionUsedAt(board, x, 0, West) = 1;
        *boardDirectionUsedAt(board, x, 0, East) = 1;
        *boardDirectionUsedAt(board, x, 0, North) = 1;
        *boardDirectionUsedAt(board, x, 0, NorthWest) = 1;
        *boardDirectionUsedAt(board, x, 0, NorthEast) = 1;

        *boardDirectionUsedAt(board, x, board->height - 1, West) = 1;
        *boardDirectionUsedAt(board, x, board->height - 1, East) = 1;
        *boardDirectionUsedAt(board, x, board->height - 1, South) = 1;
        *boardDirectionUsedAt(board, x, board->height - 1, SouthWest) = 1;
        *boardDirectionUsedAt(board, x, board->height - 1, SouthEast) = 1;

    }
    // special cases!
    // top gate visited
    *boardVisitedAt(board, board->width/2 - 1, 0) = 0;
    *boardVisitedAt(board, board->width/2, 0) = 0;
    *boardVisitedAt(board, board->width/2 + 1, 0) = 0;
    // bottom gate visited
    *boardVisitedAt(board, board->width/2 - 1, board->height - 1) = 0;
    *boardVisitedAt(board, board->width/2, board->height - 1) = 0;
    *boardVisitedAt(board, board->width/2 + 1, board->height - 1) = 0;
    //top gate directions
    *boardDirectionUsedAt(board, board->width/2 - 1, 0, NorthEast) = 0;
    *boardDirectionUsedAt(board, board->width/2 - 1, 0, East) = 0;
    
    *boardDirectionUsedAt(board, board->width/2, 0, North) = 0;
    *boardDirectionUsedAt(board, board->width/2, 0, NorthWest) = 0;
    *boardDirectionUsedAt(board, board->width/2, 0, NorthEast) = 0;
    *boardDirectionUsedAt(board, board->width/2, 0, West) = 0;
    *boardDirectionUsedAt(board, board->width/2, 0, East) = 0;

    *boardDirectionUsedAt(board, board->width/2 + 1, 0, NorthWest) = 0;
    *boardDirectionUsedAt(board, board->width/2 + 1, 0, West) = 0; 
    // bottom gate directions
    *boardDirectionUsedAt(board, board->width/2 - 1, board->height - 1, SouthEast) = 0;
    *boardDirectionUsedAt(board, board->width/2 - 1, board->height - 1, East) = 0;

    *boardDirectionUsedAt(board, board->width/2, board->height - 1, South) = 0;
    *boardDirectionUsedAt(board, board->width/2, board->height - 1, SouthWest) = 0;
    *boardDirectionUsedAt(board, board->width/2, board->height - 1, SouthEast) = 0;
    *boardDirectionUsedAt(board, board->width/2, board->height - 1, East) = 0;
    *boardDirectionUsedAt(board, board->width/2, board->height - 1, West) = 0;

    *boardDirectionUsedAt(board, board->width/2 + 1, board->height - 1, SouthWest) = 0;
    *boardDirectionUsedAt(board, board->width/2 + 1, board->height - 1, West) = 0;
}

bool* boardVisitedAt(Board* board, uint16_t x, uint16_t y)
{
    return &board->visited[x + y * board->width]; // return board->visited + x + y * board->width;
}
bool* boardDirectionUsedAt(Board* board, uint16_t x, uint16_t y, Direction direction)
{
    return &board->directionUsed[x*board->height*8 + y*8 + direction];
}