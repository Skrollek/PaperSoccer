#include "draw.h"
void draw(Board* board)
{
    for(int x = 1; x < board->width; ++x)
    {
            putchar(' ');
            putchar('_');
    }
    for(int y = 1; y < board->height; ++y)
    {
        putchar('\n');
        for(int x = 1; x < board->width; ++x)
        {
            putchar('|');
            putchar('_');
        }
        putchar('|');
    }
}