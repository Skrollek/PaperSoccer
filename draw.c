#include "draw.h"

void draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer userData)
{
    Board *board = ((ActivationData*)userData)->board;
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    double squareSize = 600.0/(board->width-1);
    if(600.0/(board->height - 1) < squareSize) squareSize = 600.0/(board->height - 1);
    cairo_translate(cr, 400-squareSize*((board->width)/2), 400-squareSize*((board->height)/2)); // change
    
    //drawing board section
    cairo_rectangle(cr, squareSize*((board->width)/2) - squareSize, 0, squareSize, squareSize);
    cairo_rectangle(cr, squareSize*((board->width)/2), 0, squareSize, squareSize);
    for(int y = 1; y < board->height-2; ++y) // change
    {
        for(int x = 0; x < board->width-1; ++x)
        {
            cairo_rectangle(cr, squareSize*x, squareSize*y, squareSize, squareSize);
        }
    }
    cairo_rectangle(cr, squareSize*((board->width)/2) - squareSize, squareSize*((board->height - 2)), squareSize, squareSize);
    cairo_rectangle(cr, squareSize*((board->width)/2), squareSize*((board->height - 2)), squareSize, squareSize);
    cairo_stroke(cr);

    // drawing used moves section
    cairo_set_source_rgb(cr, 0, 0, 255);
    cairo_set_line_width(cr, 2);

    cairo_move_to(cr, squareSize*(((board->width)/2)-1), squareSize);
    cairo_line_to(cr, squareSize*(((board->width)/2)-1), 0);

    cairo_move_to(cr, squareSize*(((board->width)/2)-1),0);
    cairo_line_to(cr, squareSize*(((board->width)/2)+1), 0);

    cairo_move_to(cr, squareSize*(((board->width)/2)+1), 0);
    cairo_line_to(cr, squareSize*(((board->width)/2)+1), squareSize);

    for(int y = 1; y < board->height-1; ++y)
    {
        for(int x = 0; x < board->width; ++x)
        {
            if(*boardDirectionUsedAt(board, x, y, West) && x != 0)
            {
                cairo_move_to(cr, squareSize*x, squareSize*y);
                cairo_line_to(cr, squareSize*x - squareSize, squareSize*y);
            }
            if(*boardDirectionUsedAt(board, x, y, SouthWest) && x != 0 && y != board->height-2) 
            {
                cairo_move_to(cr, squareSize*x, squareSize*y);
                cairo_line_to(cr, squareSize*x - squareSize, squareSize*y + squareSize);
            }
            if(*boardDirectionUsedAt(board, x, y, South) && y != board->height-2) 
            {
                cairo_move_to(cr, squareSize*x, squareSize*y);
                cairo_line_to(cr, squareSize*x, squareSize*y + squareSize);
            }
            if(*boardDirectionUsedAt(board, x, y, SouthEast) && x != board->width - 1 && y != board->height-2) 
            {
                cairo_move_to(cr, squareSize*x, squareSize*y);
                cairo_line_to(cr, squareSize*x + squareSize, squareSize*y + squareSize);
            }
            if(*boardDirectionUsedAt(board, x, y, East) && x != board->width - 1 ) 
            {
                cairo_move_to(cr, squareSize*x, squareSize*y);
                cairo_line_to(cr, squareSize*x + squareSize, squareSize*y);
            }
        }
    }
    cairo_move_to(cr, squareSize*(((board->width)/2)-1), (board->height-2)*squareSize);
    cairo_line_to(cr, squareSize*(((board->width)/2)-1), (board->height-1)*squareSize);

    cairo_move_to(cr, squareSize*(((board->width)/2)-1),(board->height-1)*squareSize);
    cairo_line_to(cr, squareSize*(((board->width)/2)+1), (board->height-1)*squareSize);

    cairo_move_to(cr, squareSize*(((board->width)/2)+1), (board->height-1)*squareSize);
    cairo_line_to(cr, squareSize*(((board->width)/2)+1), (board->height-2)*squareSize);
    cairo_stroke(cr);

    // drawing possible moves section
    cairo_set_source_rgb(cr, 0,100,0);
    cairo_set_line_width(cr, 1);
    uint8_t possibleMoves = calculatePossibleMoves(board,board->ballX, board->ballY); 
    for(int i = 0; i < 8; ++i)
    {
        if(possibleMoves & (1 << i))
        {
            int32_t coords = directionToCoords(i);
            int16_t coordX = getXCoordFromInt(coords);
            int16_t coordY = getYCoordFromInt(coords);
            cairo_arc(cr, squareSize*(board->ballX) + coordX*squareSize, squareSize*(board->ballY) + coordY*squareSize, 4, 0, 6.2830);
            cairo_fill_preserve(cr);
            cairo_stroke(cr);
        }
            
    }

    // drawing ball section
    cairo_set_source_rgb(cr, 255, 0, 0);
    cairo_set_line_width(cr, 1);
    cairo_arc(cr, squareSize*(board->ballX), squareSize*(board->ballY), 4, 0, 6.2830);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);
}